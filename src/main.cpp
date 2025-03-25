#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "reg_handler.h"
#include "sql/pgconn.h"
#include "task.h"


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



    RegHandler regHandler(&engine, db->connection().get());
    engine.rootContext()->setContextProperty("regHandler", &regHandler);

    // add task_hadeler
    Task task(db->connection().get());

    // engine.rootContext()->setContextProperty("taskHandler", &taskHandler);

    engine.load(QUrl(QStringLiteral("qrc:/ui/login.qml"))); 

    return app.exec();
}