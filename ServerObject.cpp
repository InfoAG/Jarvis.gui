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


    //server = new QLineEdit("176.198.129.70");
    serverLabel = new QLabel("Server: ");
    nickLabel = new QLabel("Nick: ");
    pwdLabel = new QLabel("Password: ");
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
    sidebar = new QTabWidget;

    users = new QListWidget;
    variables = new QListWidget;
    functions = new QListWidget;

    sidebar->addTab(users, "Users");
    sidebar->addTab(variables, "Variables");
    sidebar->addTab(functions,"Functions");
    sidebar->setTabPosition(QTabWidget::East);

    QVBoxLayout* vbox = new QVBoxLayout;
    QHBoxLayout* hbox2 = new QHBoxLayout;
    hbox2->addWidget(input);
    hbox2->addWidget(processButton);
    hbox1 = new QHBoxLayout;
    hbox1->addWidget(output,3);
    hbox1->addWidget(sidebar,1);
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
    connect(client,SIGNAL(definedVariable(QString,QString,QString)),this,SLOT(definedVariable(QString,QString,QString)));
    connect(client,SIGNAL(newClient(QString,QString)),this,SLOT(newClient(QString,QString)));
    connect(client,SIGNAL(clientLeft(QString,QString)),this,SLOT(clientLeft(QString,QString)));
}



void ServerObject::receiveInitInfo(QStringList globalRooms,QList<ModulePackage> packages)
{
    stackedWidget->setCurrentWidget(infoPage);

    for(int i = 0; i < globalRooms.size(); i++)
    {
        QStandardItem* item = new QStandardItem(globalRooms[i]);
        item->setEditable(false);
        roomModel->appendRow(item);
    }

    for(int i = 0; i < packages.size(); i++)
    {
        QStandardItem* packageItem = new QStandardItem(packages[i].name);
        packageItem->setEditable(false);
        packageModel->appendRow(packageItem);

        if(packages[i].binaryOperators.size() != 0)
        {
            QStandardItem* binOp = new QStandardItem("Binary Operators");
            binOp->setEditable(false);
            packageItem->appendRow(binOp);
            for(int j = 0; j < packages[i].binaryOperators.size(); j++)
            {
                QStandardItem* item = new QStandardItem(packages[i].binaryOperators[j].name);
                item->setEditable(false);
                binOp->appendRow(item);
            }
        }

        if(packages[i].unaryOperators.size() != 0)
        {
            QStandardItem* unOp = new QStandardItem("Unary Operators");
            unOp->setEditable(false);
            packageItem->appendRow(unOp);
            for(int j = 0; j < packages[i].unaryOperators.size(); j++)
            {
                QStandardItem* item = new QStandardItem(packages[i].unaryOperators[j].name);
                item->setEditable(false);
                unOp->appendRow(item);
            }
        }

        if(packages[i].terminals.size() != 0)
        {
            QStandardItem* terminals = new QStandardItem("Terminals");
            terminals->setEditable(false);
            packageItem->appendRow(terminals);
            for(int j = 0; j < packages[i].terminals.size(); j++)
            {
                QStandardItem* item = new QStandardItem(packages[i].terminals[j].name);
                item->setEditable(false);
                terminals->appendRow(item);
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
        this->roomContent[name].userWidget = this->users;
        this->roomContent[name].varWidget = this->variables;
        this->roomContent[name].funcWidget = this->functions;
        this->roomContent[name].tab = this->sidebar;

    }
    else
    {
        this->hbox1->removeWidget(this->roomContent[currentRoom].tab);
        this->roomContent[name].tab = new QTabWidget;
        this->roomContent[name].userWidget = new QListWidget;
        this->roomContent[name].varWidget = new QListWidget;
        this->roomContent[name].funcWidget = new QListWidget;

        this->roomContent[name].tab->addTab(this->roomContent[name].userWidget, "Users");
        this->roomContent[name].tab->addTab(this->roomContent[name].varWidget, "Variables");
        this->roomContent[name].tab->addTab(this->roomContent[name].funcWidget,"Functions");
        this->roomContent[name].tab->setTabPosition(QTabWidget::East);
        this->hbox1->addWidget(this->roomContent[name].tab,1);
    }

    this->roomCounter++;
    currentRoom = name;
    emit roomOK(name,this->server->text());

    //add userlist to userWidget and sort them
    this->roomContent[currentRoom].userWidget->addItems(info.clients);
    this->roomContent[currentRoom].userWidget->sortItems();

    //add existing variables to varWidget, setting the tooltips, checking for definition
    for(auto it = info.variables.begin(); it != info.variables.end(); ++it)
    {
        QListWidgetItem* item = new QListWidgetItem();
        item->setToolTip(it.value().first);
        if(it.value().second == "")
        {
            item->setText(it.key());
        }
        else
            item->setText(it.key()+"="+it.value().second);

        this->roomContent[currentRoom].varWidget->addItem(item);
        this->roomContent[currentRoom].varWidget->sortItems();
    }


}


void ServerObject::roomChanged(QString name)
{
    this->output->setText(roomContent[name].stringContent);

    this->hbox1->removeWidget(this->roomContent[currentRoom].tab);
    this->roomContent[currentRoom].tab->setParent(0);
    this->hbox1->addWidget(this->roomContent[name].tab,1);
    currentRoom = name;
    //ensure vis
    ensureVisibility();
}

void ServerObject::msgInRoom(QString room, QString sender, QString msg)
{
    roomContent[room].stringContent += sender + ": " + msg + "\n";
    if(currentRoom == room)
    {
        this->output->setText(roomContent[room].stringContent);
        //ensure vis
        ensureVisibility();
    }
}

void ServerObject::msgToRoom()
{
    this->client->msgToRoom(currentRoom,this->input->text());
    this->input->clear();
    //ensure vis
    ensureVisibility();
}




void ServerObject::declaredVar(QString rm, QString id , QString tp)
{
    QListWidgetItem* item = new QListWidgetItem(id);
    item->setToolTip(tp);
    this->roomContent[rm].varWidget->addItem(item);
    this->roomContent[rm].varWidget->sortItems();
}

void ServerObject::definedVariable(QString rm, QString id, QString def)
{
    if(this->roomContent[rm].varWidget->findItems(id+"=", Qt::MatchContains).length() != 0)
        this->roomContent[rm].varWidget->findItems(id+"=", Qt::MatchContains).at(0)->setText(id+ "=" + def);
    else if(this->roomContent[rm].varWidget->findItems(id, Qt::MatchExactly).length() != 0)
        this->roomContent[rm].varWidget->findItems(id, Qt::MatchExactly).at(0)->setText(id+ "=" + def);
}


void ServerObject::newClient(QString rm, QString nk)
{
    this->roomContent[rm].userWidget->addItem(nk);
    this->roomContent[rm].userWidget->sortItems();
}

void ServerObject::clientLeft(QString rm, QString nk)
{
    QListWidgetItem* item = this->roomContent[rm].userWidget->findItems(nk,Qt::MatchExactly).at(0);
    delete item;

}

void ServerObject::setCurrentPage(pageType type)
{
    switch(type)
    {
        case INFO:
            stackedWidget->setCurrentWidget(this->infoPage);
            break;
        case LOGIN:
            stackedWidget->setCurrentWidget(this->loginPage);
            break;
        case SERVER:
            stackedWidget->setCurrentWidget(this->serverPage);
            break;
    }
}

void ServerObject::ensureVisibility()
{
    QTextCursor c = output->textCursor();
    c.movePosition(QTextCursor::End);
    output->setTextCursor(c);
}
