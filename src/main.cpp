#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <exception>
#include <QObject>
#include <QQuickView>
#include <QQuickItem>

// #include "libpq-fe.h"
#include "sql/pgconn.h"
#include "sql/user_query.h"
#include "user.h"


int main(int argc, char *argv[]) {
    // init application with graph engine
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
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

    Query query(db.connection().get());
    User user("vlad", "vlad13373", &query);
    // user.regUser();
    user.login();

    // QQuickView* myObject;
    // QQuickItem* object = myObject->rootObject();
    // QObject textin = object->findChild<QObject>("loginInput");


    // QString input = textin.property("text").toString();
    // qDebug() << "LOGIN INPUT: " << input << " \n";
    


    return app.exec();
}