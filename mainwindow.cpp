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
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),this,SLOT(activate(QModelIndex)));
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

    connect(newServer,SIGNAL(receivedInitInfo(QString)),this,SLOT(receiveInitInfo(QString)));
    connect(newServer,SIGNAL(roomOK(QString,QString)),this,SLOT(roomOK(QString,QString)));
}

void MainWindow::receiveInitInfo(QString name)
{
    currentServer = name;
    this->serverObjects[name] = (ServerObject*)QObject::sender(); //associate ServerName with its ServerObject
    QStandardItem* serverItem = new QStandardItem(name);
    serverItem->setEditable(false);
    this->root->appendRow(serverItem);
    serverItem->appendRow(new QStandardItem("new Room"));
}

void MainWindow::activate(QModelIndex index) //item clicked
{
    QString room;
    QString server;
    if(treeModel->itemFromIndex(index)->isEditable() == false)
    {
        if(treeModel->itemFromIndex(index) != 0 && treeModel->itemFromIndex(index)->parent() != 0)
        {
            //server and roomnode
            room = treeModel->itemFromIndex(index)->text();
            server = treeModel->itemFromIndex(index)->parent()->text();
            serverObjects[server]->roomChanged(room);

            serverObjects[server]->setCurrentPage(ServerObject::SERVER);
        }
        else if(treeModel->itemFromIndex(index) != 0)
        {
            //servernode
            server = treeModel->itemFromIndex(index)->text();

            serverObjects[server]->setCurrentPage(ServerObject::INFO);
        }

        if(server != currentServer)
        {
            //reset currently shown server
            serverObjects[currentServer]->getWidget()->setParent(NULL);
            ui->horizontalLayout->addWidget(serverObjects[server]->getWidget());
            ui->horizontalLayout->setStretch(1,4);

            currentServer = server;
        }
    }


}

void MainWindow::modelDataChanged(QStandardItem *item)
{
    if(item->text() != "new Room" && item->isEditable())
    {
        QString server = item->parent()->text();
        item->setEditable(false);

        serverObjects[server]->enterRoom(item->text());


        if(server != currentServer)
        {
            //reset currently shown server
            QLayoutItem* item = ui->horizontalLayout->itemAt(1);
            ui->horizontalLayout->removeItem(item);
            ui->horizontalLayout->addWidget(serverObjects[server]->getWidget());
            ui->horizontalLayout->setStretch(1,4);
        }

    }
}

void MainWindow::roomOK(QString name, QString server)
{
    this->treeModel->findItems(server).at(0)->appendRow(new QStandardItem("new Room"));

}








