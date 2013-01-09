#include "ServerObject.h"

ServerObject::ServerObject(int height, int width)
{
    roomCounter = 0;
    stackedWidget = new QStackedWidget;

    loginPage = new QWidget;
    loginLayout = new QGridLayout;
    frame = new QFrame;
    frame->setStyleSheet(".QFrame {border: 3px solid gray;border-radius: 40px;background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #FF6600, stop: 1 #FFCC99);}");
    QGridLayout* innerLayout = new QGridLayout(frame);

    serverLabel = new QLabel("Server:");
    nickLabel = new QLabel("Nick:");
    pwdLabel = new QLabel("Password:");
    portLabel = new QLabel("Port:");
    server = new QLineEdit("localhost");
    nick = new QLineEdit("Nick");
    pwd = new QLineEdit("pwd");
    port = new QLineEdit("4200");
    loginButton = new QPushButton("Login");

    innerLayout->addWidget(serverLabel,0,0);
    innerLayout->addWidget(server,0,1);
    innerLayout->addWidget(nickLabel,1,0);
    innerLayout->addWidget(nick,1,1);
    innerLayout->addWidget(pwdLabel,2,0);
    innerLayout->addWidget(pwd,2,1);
    innerLayout->addWidget(portLabel,3,0);
    innerLayout->addWidget(port,3,1);
    innerLayout->addWidget(loginButton,4,0);


    loginLayout->addWidget(frame,1,1);
    loginLayout->addItem(new QSpacerItem(width/6,1),1,2);
    loginLayout->addItem(new QSpacerItem(width/6,1),2,0);
    loginLayout->addItem(new QSpacerItem(1,height/6),0,1);
    loginLayout->addItem(new QSpacerItem(1,height/6),2,1);
    loginPage->setLayout(loginLayout);

    serverPage = new QWidget;

    input = new QLineEdit;
    processButton = new QPushButton("Process");
    output = new QTextEdit;
    output->setReadOnly(true);
    info = new QTabWidget;

    user = new QListWidget;
    variables = new QListWidget;
    functions = new QListWidget;

    info->addTab(user, "Users");
    info->addTab(variables, "Variables");
    info->addTab(functions,"Functions");
    info->setTabPosition(QTabWidget::East);

    QVBoxLayout* vbox = new QVBoxLayout;
    QHBoxLayout* hbox2 = new QHBoxLayout;
    hbox2->addWidget(input);
    hbox2->addWidget(processButton);
    QHBoxLayout* hbox1 = new QHBoxLayout;
    hbox1->addWidget(output,3);
    hbox1->addWidget(info,1);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    serverPage->setLayout(vbox);


    infoPage = new QWidget;

    packageView = new QTreeView;
    packageModel = new QStandardItemModel;
    roomView = new QListView;
    roomModel = new QStandardItemModel;

    packageView->setModel(packageModel);
    packageView->setHeaderHidden(true);
    roomView->setModel(roomModel);

    QHBoxLayout* infoLayout = new QHBoxLayout;
    infoLayout->addWidget(packageView);
    infoLayout->addWidget(roomView);
    infoPage->setLayout(infoLayout);




    stackedWidget->addWidget(loginPage);
    stackedWidget->addWidget(serverPage);
    stackedWidget->addWidget(infoPage);


    connect(loginButton,SIGNAL(clicked()),this,SLOT(performLogin()));
    connect(input,SIGNAL(returnPressed()),this,SLOT(msgToRoom()));
    connect(processButton,SIGNAL(clicked()),this,SLOT(msgToRoom()));
}

void ServerObject::performLogin()
{
    this->loginButton->setEnabled(false);
    this->loginButton->setText("Connecting...");
    client = new JarvisClient(this->server->text(),this->port->text().toInt(),this->nick->text(),this->pwd->text());


    connect(client,SIGNAL(receivedInitInfo(QStringList,QList<ModulePackage>)),this,SLOT(receiveInitInfo(QStringList,QList<ModulePackage>)));
    connect(client,SIGNAL(enteredRoom(QString,Room)),this,SLOT(enteredRoom(QString,Room)));
    connect(client,SIGNAL(msgInRoom(QString,QString,QString)),this,SLOT(msgInRoom(QString,QString,QString)));
    connect(client,SIGNAL(declaredVariable(QString,QString,QString)),this,SLOT(declaredVar(QString,QString,QString)));
}



void ServerObject::receiveInitInfo(QStringList globalRooms,QList<ModulePackage> packages)
{
    stackedWidget->setCurrentWidget(infoPage);

    for(int i = 0; i < globalRooms.size(); i++)
    {
        roomModel->appendRow(new QStandardItem(globalRooms[i]));
    }

    for(int i = 0; i < packages.size(); i++)
    {
        QStandardItem* packageItem = new QStandardItem(packages[i].name);
        packageModel->appendRow(packageItem);

        if(packages[i].binaryOperators.size() != 0)
        {
            QStandardItem* binOp = new QStandardItem("Binary Operators");
            packageItem->appendRow(binOp);
            for(int j = 0; j < packages[i].binaryOperators.size(); j++)
            {
                binOp->appendRow(new QStandardItem(packages[i].binaryOperators[j].name));
            }
        }

        if(packages[i].unaryOperators.size() != 0)
        {
            QStandardItem* unOp = new QStandardItem("Unary Operators");
            packageItem->appendRow(unOp);
            for(int j = 0; j < packages[i].unaryOperators.size(); j++)
            {
                unOp->appendRow(new QStandardItem(packages[i].unaryOperators[j].name));
            }
        }

        if(packages[i].terminals.size() != 0)
        {
            QStandardItem* terminals = new QStandardItem("Terminals");
            packageItem->appendRow(terminals);
            for(int j = 0; j < packages[i].terminals.size(); j++)
            {
                terminals->appendRow(new QStandardItem(packages[i].terminals[j].name));
            }
        }


    }

    emit receivedInitInfo(this->server->text());
}

void ServerObject::enterRoom(QString room)
{
    this->client->enterRoom(room);
}

void ServerObject::enteredRoom(QString name, Room info)
{
    if(roomCounter == 0)
    {
        stackedWidget->setCurrentWidget(serverPage);
    }

    this->roomCounter++;
    currentRoom = name;
    emit roomOK(name,this->server->text());
}


void ServerObject::roomChanged(QString name)
{
    currentRoom = name;
    this->output->setText(roomContent[name].stringContent);
}

void ServerObject::msgInRoom(QString room, QString sender, QString msg)
{
    roomContent[room].stringContent += sender + ": " + msg + "\n";
    if(currentRoom == room)
    {
        this->output->setText(roomContent[room].stringContent);
    }
}

void ServerObject::msgToRoom()
{
    this->client->msgToRoom(currentRoom,this->input->text());
    this->input->clear();
}




void ServerObject::declaredVar(QString rm, QString id , QString tp)
{
    //roomContent[rm].vars.append(new)
    QListWidgetItem* item = new QListWidgetItem(id);
    item->setToolTip(tp);
    this->variables->addItem(item);
}
