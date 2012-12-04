#ifndef SERVEROBJECT_H
#define SERVEROBJECT_H

#include <QWidget>
#include <QStackedWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QSpacerItem>
#include <QStringList>
#include <QTextEdit>
#include <QTabWidget>
#include <QListWidget>
#include <QMap>


#include "ModulePackage.h"
#include "JarvisClient.h"
#include "Room.h"

class ServerObject : public QWidget
{
    Q_OBJECT
public:
    ServerObject(int height, int width);
    QWidget* getWidget() {return this->stackedWidget;}
    void enterRoom(QString room);
    void roomChanged(QString name);

private:
    QStackedWidget* stackedWidget;

    QLabel* serverLabel; //loginPage stuff
    QLineEdit* server;
    QLabel* nickLabel;
    QLineEdit* nick;
    QLabel* pwdLabel;
    QLineEdit* pwd;
    QLabel* portLabel;
    QLineEdit* port;
    QPushButton* loginButton;
    QFrame* frame;


    QLineEdit* input; //serverPage stuff
    QPushButton* processButton;
    QTextEdit* output;
    QTabWidget* info;
    QListWidget* user;
    QListWidget* variables;
    QListWidget* functions;




    QWidget* loginPage;
    QWidget* serverPage;
    QGridLayout* loginLayout;

    JarvisClient* client;




signals:
    void receivedInitInfo(QStringList globalRooms,QList<ModulePackage> packages, QString name);
    void roomOK(QString name, QString server);
private slots:
    void performLogin();
    void receiveInitInfo(QStringList,QList<ModulePackage>);
    void enteredRoom(QString name, Room info);

};

#endif // SERVEROBJECT_H
