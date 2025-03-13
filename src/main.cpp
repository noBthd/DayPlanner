#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <exception>
#include <QObject>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlProperty>

// #include "libpq-fe.h"
#include "sql/pgconn.h"
// #include "sql/user_query.h"
// #include "user.h"
#include "reg_handler.h"


int main(int argc, char *argv[]) {
    // init application with graph engine
    QApplication app(argc, argv);
    
    QQmlApplicationEngine engine;

    RegHandler regHandler;
    engine.rootContext()->setContextProperty("regHandler", &regHandler);

    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml"))); 
    
    // db conn
    PGConnection db;
    
    try {
        if (db.connection()) {
            qDebug() << "db connected succesfully\n";
        } else {
            qDebug() << "failed to connect db\n";
            return 1;
        }
    } catch (const std::exception& e){
        qDebug() << "Exception: " << e.what() << "\n";
        return 1;
    }

    return app.exec();
}