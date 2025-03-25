#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "reg_handler.h"
#include "sql/pgconn.h"


int main(int argc, char *argv[]) {
    // init application with graph engine
    QApplication app(argc, argv);
    
    QQmlApplicationEngine engine;

    // db conn
    PGConnection* db;
    try {
        db = new PGConnection(); 
        if (db->connection()) {
            qDebug() << "db connected successfully";
        } else {
            qDebug() << "Failed to connect db";
        }
    } catch (const std::exception& e) {
        qDebug() << "Exception: " << e.what();
    }

    RegHandler regHandler(&engine, db);
    engine.rootContext()->setContextProperty("regHandler", &regHandler);

    engine.load(QUrl(QStringLiteral("qrc:/ui/login.qml"))); 

    return app.exec();
}