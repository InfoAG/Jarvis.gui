#ifndef QMLJARVISCLIENT_H
#define QMLJARVISCLIENT_H

#include "JarvisClient.h"

class QMLJarvisClient : public JarvisClient
{
    Q_OBJECT

public:
    QMLJarvisClient();

private slots:
    void receivedInitInfo(const QStringList &scopes, const QList<ModulePackage> &pkgs);
    void pkgLoaded(const ModulePackage &pkg) { emit pkgLoadedQML(QVariant::fromValue(pkg)); }
    void enteredScope(const QString &name, const Scope &info) { emit enteredScopeQML(name, QVariant::fromValue(info)); }

signals:
    void pkgLoadedQML(const QVariant &pkg);
    void enteredScopeQML(const QString &name, const QVariant &info);
    void receivedInitInfo(const QVariant &scopes, const QVariant &pkgs);
};

#endif // QMLJARVISCLIENT_H
