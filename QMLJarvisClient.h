#ifndef QMLJARVISCLIENT_H
#define QMLJARVISCLIENT_H

#include "JarvisClient.h"
#include "QMLModulePackage.h"
#include "QMLRoom.h"

class QMLJarvisClient : public JarvisClient
{
    Q_OBJECT

public:
    QMLJarvisClient();

private slots:
    void receivedInitInfo(const QStringList &rooms, const QList<ModulePackage> &pkgs);
    void pkgLoaded(const ModulePackage &pkg) { emit pkgLoadedQML(new QMLModulePackage(pkg)); }
    void enteredRoom(const QString &name, const Room &info) { emit enteredRoomQML(name, new QMLRoom(info)); }

signals:
    void pkgLoadedQML(QObject *pkg);
    void enteredRoomQML(const QString &name, QObject *info);
    void receivedInitInfoQML(const QStringList &rooms, const QList<QObject*> &pkgs);
};

#endif // QMLJARVISCLIENT_H
