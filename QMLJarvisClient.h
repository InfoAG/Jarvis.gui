#ifndef QMLJARVISCLIENT_H
#define QMLJARVISCLIENT_H

#include "JarvisClient.h"
#include "QMLModulePackage.h"
#include "QMLScope.h"

class QMLJarvisClient : public JarvisClient
{
    Q_OBJECT

public:
    QMLJarvisClient();

private slots:
    void receivedInitInfo(const QStringList &scopes, const QList<ModulePackage> &pkgs);
    void pkgLoaded(const ModulePackage &pkg) { emit pkgLoadedQML(new QMLModulePackage(pkg)); }
    void enteredScope(const QString &name, const Scope &info) { emit enteredScopeQML(name, new QMLScope(info)); }

signals:
    void pkgLoadedQML(QObject *pkg);
    void enteredScopeQML(const QString &name, QObject *info);
    void receivedInitInfoQML(const QStringList &scopes, const QList<QObject*> &pkgs);
};

#endif // QMLJARVISCLIENT_H
