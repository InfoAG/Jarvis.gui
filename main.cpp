#include <QApplication>
#include <QtDeclarative>
#include "qmlapplicationviewer.h"
#include "QMLJarvisClient.h"
#include "Room.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    qmlRegisterType<QMLJarvisClient>("QMLJarvisClient",0,1,"QMLJarvisClient");
    qmlRegisterType<QMLRoom>();
    qmlRegisterType<QMLOperatorModule>();
    qmlRegisterType<QMLFunctionModule>();
    qmlRegisterType<QMLFunctionDefinition>();

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setSource(QUrl("qrc:/qml/GUI/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
