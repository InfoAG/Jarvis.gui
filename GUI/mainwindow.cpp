#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->treeModel = new QStandardItemModel();
    ui->treeView->header()->hide();
    ui->treeView->setModel(treeModel);
    ui->treeView->setSortingEnabled(true);
    root = treeModel->invisibleRootItem();


    connect(ui->newServerConnectionAction,SIGNAL(triggered()),this,SLOT(newServerConnection()));
    connect(ui->treeView,SIGNAL(activated(QModelIndex)),this,SLOT(activate(QModelIndex)));
    connect(this->treeModel,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(modelDataChanged(QStandardItem*)));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::newServerConnection()
{
    QLayoutItem* item = ui->horizontalLayout->itemAt(1);
    if(item)
    {
        ui->horizontalLayout->removeItem(item);
    }

    ServerObject* newServer = new ServerObject(this->height(),this->width());
    ui->horizontalLayout->addWidget(newServer->getWidget());
    ui->horizontalLayout->setStretch(1,4);

    connect(newServer,SIGNAL(receivedInitInfo(QStringList,QList<ModulePackage>,QString)),this,SLOT(receiveInitInfo(QStringList,QList<ModulePackage>,QString)));
}

void MainWindow::receiveInitInfo(QStringList globalRooms, QList<ModulePackage> packages, QString name)
{
    currentServer = name;
    this->serverObjects[name] = (ServerObject*)QObject::sender(); //associate ServerName with its ServerObject
    QStandardItem* serverItem = new QStandardItem(name);
    serverItem->setEditable(false);
    this->root->appendRow(serverItem);
    //this->root->child(ui->treeView->currentIndex().row(),0);
    serverItem->appendRow(new QStandardItem("new Room"));
}

void MainWindow::activate(QModelIndex index)
{
    if(treeModel->itemFromIndex(index) != 0 && treeModel->itemFromIndex(index)->parent() != 0)
    {
        QString room = treeModel->itemFromIndex(index)->text();
        QString server = treeModel->itemFromIndex(index)->parent()->text();

        if(server != currentServer)
        {
            QLayoutItem* item = ui->horizontalLayout->itemAt(1);
            ui->horizontalLayout->removeItem(item);
            ui->horizontalLayout->addWidget(serverObjects[server]->getWidget());
            ui->horizontalLayout->setStretch(1,4);


        }
    }


}

void MainWindow::modelDataChanged(QStandardItem *item)
{
    if(item->text() != "new Room" && item->isEditable())
    {

    }
}








