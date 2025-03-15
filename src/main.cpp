#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "reg_handler.h"


int main(int argc, char *argv[]) {
    // init application with graph engine
    QApplication app(argc, argv);
    
    QQmlApplicationEngine engine;

    RegHandler regHandler(&engine);
    engine.rootContext()->setContextProperty("regHandler", &regHandler);

    engine.load(QUrl(QStringLiteral("qrc:/ui/login.qml"))); 

    return app.exec();
}