#include <QApplication>
#include <QtDeclarative>
#include "qmlapplicationviewer.h"
#include "JarvisClient.h"
#include "Scope.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    qmlRegisterType<JarvisClient>("JarvisClient",0,1,"JarvisClient");

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("main.qml"));
    viewer.showExpanded();

    return app->exec();
}
