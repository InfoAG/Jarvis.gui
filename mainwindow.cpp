#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphicsOpacityEffect"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->treeModel = new QStandardItemModel();
    ui->treeView->header()->hide();
    ui->treeView->setModel(treeModel);
    ui->treeView->setSortingEnabled(true);

    root = treeModel->invisibleRootItem();
    ui->treeView->hide();
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
    loginLayout->addRow(tr("&Server:"), server);
    loginLayout->addRow(tr("&Nick:"), nick);
    loginLayout->addRow(tr("&Password:"), pwd);
    loginLayout->addRow(tr("&Port:"), port);
    loginLayout->addRow(loginButton);
    loginWidget = new QWidget;
    loginWidget->setLayout(loginLayout);
    ui->verticalLayout->insertWidget(0,loginWidget);
    loginWidget->hide();

    this->currentServer = "";





    connect(ui->newServerConnectionAction,SIGNAL(triggered()),this,SLOT(showLogin()));
    connect(this->loginButton,SIGNAL(clicked()),this,SLOT(newServerConnection()));
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),this,SLOT(activate(QModelIndex)));
    connect(this->treeModel,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(modelDataChanged(QStandardItem*)));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLogin()
{

    int oldHeight = ui->treeView->height();

    this->loginWidget->show();

    QParallelAnimationGroup* animGroup = new QParallelAnimationGroup(this);

    QPropertyAnimation *posAnimation = new QPropertyAnimation(this->loginWidget, "pos", this);
    posAnimation->setDuration(500);
    posAnimation->setStartValue(QPoint(this->loginWidget->x(),this->loginWidget->y()-this->loginWidget->height()));
    posAnimation->setEndValue(QPoint(this->loginWidget->x(),this->loginWidget->y()));
    animGroup->addAnimation(posAnimation);


    QPropertyAnimation* resizeAnimation1 = new QPropertyAnimation(ui->treeView, "geometry", this);
    resizeAnimation1->setDuration(500);
    resizeAnimation1->setStartValue(QRect(ui->treeView->x(),ui->treeView->y()-this->loginWidget->height(),ui->treeView->width(),oldHeight-7));
    resizeAnimation1->setEndValue(QRect(ui->treeView->x(),ui->treeView->y(),ui->treeView->width(),ui->treeView->height()));
    animGroup->addAnimation(resizeAnimation1);


    QPropertyAnimation* resizeAnimation2;
    if(this->serverObjects[currentServer])
    {
        QWidget* wid = this->serverObjects[currentServer]->getWidget();
        resizeAnimation2 = new QPropertyAnimation(wid, "geometry", this);
        resizeAnimation2->setDuration(500);
        resizeAnimation2->setStartValue(QRect(wid->x(),wid->y()-this->loginWidget->height(),wid->width(),oldHeight-7));
        resizeAnimation2->setEndValue(QRect(wid->x(),wid->y(),wid->width(),wid->height()));
        animGroup->addAnimation(resizeAnimation2);
    }

    animGroup->start();

}

void MainWindow::hideLogin()
{

    QParallelAnimationGroup* animGroup = new QParallelAnimationGroup(this);

    QPropertyAnimation *posAnimation = new QPropertyAnimation(this->loginWidget, "pos", this);
    posAnimation->setDuration(500);
    posAnimation->setStartValue(QPoint(this->loginWidget->x(),this->loginWidget->y()));
    posAnimation->setEndValue(QPoint(this->loginWidget->x(),this->loginWidget->y()-this->loginWidget->height()));
    animGroup->addAnimation(posAnimation);


    QPropertyAnimation* resizeAnimation1 = new QPropertyAnimation(ui->treeView, "geometry", this);
    resizeAnimation1->setDuration(500);
    resizeAnimation1->setStartValue(QRect(ui->treeView->x(),ui->treeView->y(),ui->treeView->width(),ui->treeView->height()));
    resizeAnimation1->setEndValue(QRect(ui->treeView->x(),ui->treeView->y()-this->loginWidget->height(),ui->treeView->width(),ui->treeView->maximumHeight()));
    animGroup->addAnimation(resizeAnimation1);


    QPropertyAnimation* resizeAnimation2;
    if(this->serverObjects[currentServer])
    {
        QWidget* wid = this->serverObjects[currentServer]->getWidget();
        resizeAnimation2 = new QPropertyAnimation(wid, "geometry", this);
        resizeAnimation2->setDuration(500);
        resizeAnimation2->setStartValue(QRect(wid->x(),wid->y(),wid->width(),wid->height()));
        resizeAnimation2->setEndValue(QRect(wid->x(),wid->y()-this->loginWidget->height(),wid->width(),wid->maximumHeight()));
        animGroup->addAnimation(resizeAnimation2);
    }

    animGroup->start();

    connect(animGroup, SIGNAL(finished()), this->loginWidget, SLOT(hide()));

}



void MainWindow::newServerConnection()
{
    QLayoutItem* item = ui->horizontalLayout->itemAt(1);
    if(item)
    {
        ui->horizontalLayout->removeItem(item);
    }

    ServerObject* newServer = new ServerObject(this->height(),this->width());
    newServer->performLogin(this->server->text(),this->port->text().toInt(), this->nick->text(), this->pwd->text());

    //this->loginWidget->hide();
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








