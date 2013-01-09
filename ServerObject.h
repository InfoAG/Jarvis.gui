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
#include <QTreeView>
#include <QStandardItemModel>
#include <QListView>


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
    unsigned int roomCounter;

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

    QTreeView* packageView; //infoPage stuff
    QStandardItemModel* packageModel;
    QListView* roomView;
    QStandardItemModel* roomModel;



    QWidget* loginPage;
    QWidget* serverPage;
    QWidget* infoPage;
    QGridLayout* loginLayout;

    JarvisClient* client;

    struct roomData
    {
        QString stringContent;
        QList<QListWidgetItem*> vars;
        QList<QListWidgetItem*> funcs;
        QList<QListWidgetItem*> user;
    };

    QMap<QString,roomData> roomContent;
    QString currentRoom;





signals:
    void receivedInitInfo(QString name);
    void roomOK(QString name, QString server);
private slots:
    void performLogin();
    void receiveInitInfo(QStringList,QList<ModulePackage>);
    void enteredRoom(QString name, Room info);
    void msgInRoom(QString room, QString sender ,QString msg);
    void msgToRoom();
    void declaredVar(QString rm, QString id , QString tp);

};

#endif // SERVEROBJECT_H
