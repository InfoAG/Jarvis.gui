#include "QMLJarvisClient.h"

QMLJarvisClient::QMLJarvisClient()
{
    QObject::connect(this, SIGNAL(receivedInitInfo(const QStringList &, const QList<ModulePackage>&)), SLOT(receivedInitInfo(const QStringList &, const QList<ModulePackage> &)));
    QObject::connect(this, SIGNAL(enteredRoom(QString,Room)), SLOT(enteredRoom(QString,Room)));
    QObject::connect(this, SIGNAL(pkgLoaded(ModulePackage)), SLOT(pkgLoaded(ModulePackage)));
}

void QMLJarvisClient::receivedInitInfo(const QStringList &rooms, const QList<ModulePackage>& pkgs)
{
    QList<QObject*> qmlPkgs;
    std::transform(pkgs.begin(), pkgs.end(), std::back_inserter(qmlPkgs), [](const ModulePackage &item) {
            return new QMLModulePackage(item);
        });
    emit receivedInitInfoQML(rooms, qmlPkgs);
}
