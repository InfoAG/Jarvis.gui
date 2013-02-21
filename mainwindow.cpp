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
    ui->treeView->setMinimumWidth(70);
    this->firstLogin = true;

    loginLayout = new QFormLayout;
    //server = new QLineEdit("176.198.129.70");
    server = new QLineEdit("localhost");
    nick = new QLineEdit("Nick");
    pwd = new QLineEdit("pwd");
    pwd->setEchoMode( QLineEdit::Password );
    port = new QLineEdit("4200");
    loginButton = new QPushButton("Login");
    cancelButton = new QPushButton("Cancel");
    loginLayout->addRow(tr("&Server:"), server);
    loginLayout->addRow(tr("&Nick:"), nick);
    loginLayout->addRow(tr("&Password:"), pwd);
    loginLayout->addRow(tr("&Port:"), port);
    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(loginButton);
    buttonsLayout->addWidget(cancelButton);
    loginLayout->addRow(buttonsLayout);
    loginWidget = new QWidget;
    loginWidget->setLayout(loginLayout);
    loginWidget->setMaximumHeight(0);
    widgetSurrogate = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->verticalLayout->addSpacerItem(widgetSurrogate);
    ui->verticalLayout->insertWidget(0,loginWidget);
    this->currentServer = "";

    ui->treeView->hide();





    connect(ui->newServerConnectionAction,SIGNAL(triggered()),this,SLOT(showLogin()));
    connect(this->loginButton,SIGNAL(clicked()),this,SLOT(newServerConnection()));
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),this,SLOT(activate(QModelIndex)));
    connect(this->treeModel,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(modelDataChanged(QStandardItem*)));
    connect(this->cancelButton, SIGNAL(clicked()),this,SLOT(hideLogin()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLogin()
{

    QPropertyAnimation *sizeAnim = new QPropertyAnimation(this->loginWidget, "maximumHeight", this);
    sizeAnim->setDuration(500);
    sizeAnim->setStartValue(0);
    sizeAnim->setEndValue(150);
    sizeAnim->start();


}

void MainWindow::hideLogin()
{

    QPropertyAnimation *sizeAnim = new QPropertyAnimation(this->loginWidget, "maximumHeight", this);
    sizeAnim->setDuration(500);
    sizeAnim->setStartValue(150);
    sizeAnim->setEndValue(0);
    sizeAnim->start();

    if(firstLogin)
    {
        connect(sizeAnim, SIGNAL(finished()), this, SLOT(removeSpacer()));
    }

}



void MainWindow::newServerConnection()
{
    ServerObject* newServer = new ServerObject(this->height(),this->width());
    newServer->performLogin(this->server->text(),this->port->text().toInt(), this->nick->text(), this->pwd->text());

    hideLogin();

    connect(newServer,SIGNAL(receivedInitInfo(QString)),this,SLOT(receiveInitInfo(QString)));
    connect(newServer,SIGNAL(roomOK(QString,QString)),this,SLOT(roomOK(QString,QString)));
}

void MainWindow::receiveInitInfo(QString name)
{
    if(this->firstLogin)
    {
        ui->treeView->setVisible(true);
        this->firstLogin = false;
    }
    else
    {
        serverObjects[currentServer]->getWidget()->setParent(NULL);
    }
    currentServer = name;
    this->serverObjects[name] = (ServerObject*)QObject::sender(); //associate ServerName with its ServerObject
    ui->horizontalLayout->addWidget(this->serverObjects[name]->getWidget());
    ui->horizontalLayout->setStretch(1,4);
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

void MainWindow::removeSpacer()
{
    ui->verticalLayout->removeItem(this->widgetSurrogate); delete this->widgetSurrogate;
}








