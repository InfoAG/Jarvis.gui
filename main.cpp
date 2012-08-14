#include <QtGui/QApplication>
#include <QtDeclarative>
//#include "qmlapplicationviewer.h"
#include "JarvisClient.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //qmlRegisterType<JarvisClient>();

    QDeclarativeView viewer;
    //viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setSource(QUrl("qml/GUI/main.qml"));
    viewer.show();

    return app.exec();
}
