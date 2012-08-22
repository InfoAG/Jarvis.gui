#include "QMLJarvisClient.h"

QMLJarvisClient::QMLJarvisClient()
{
    QObject::connect(this, SIGNAL(receivedInitInfo(const QStringList &, const QList<ModulePackage>&)), SLOT(receivedInitInfo(const QStringList &, const QList<ModulePackage> &)));
}

void QMLJarvisClient::receivedInitInfo(const QStringList &scopes, const QList<ModulePackage>& pkgs)
{
    emit receivedInitInfo(QVariant::fromValue(scopes), QVariant::fromValue(pkgs));
}

