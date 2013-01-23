#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "JarvisClient.h"
#include <QMap>
#include <QStandardItemModel>
#include <QStackedWidget>
#include "ServerObject.h"



namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow* ui;
    QStandardItem* root;
    QStandardItemModel* treeModel;
    QMap<QString,ServerObject*> serverObjects; //QMap out of serverID and ServerObject
    QString currentServer;
    bool firstLogin;


public slots:
    void newServerConnection();
    void receiveInitInfo(QString name);
    void activate(QModelIndex index);
    void modelDataChanged(QStandardItem* item);
    void roomOK(QString name, QString server);


};

#endif // MAINWINDOW_H
