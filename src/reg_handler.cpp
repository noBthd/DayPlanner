#include "reg_handler.h"
#include "sql/pgconn.h"
#include "sql/user_query.h"

RegHandler::RegHandler(QObject* parent) 
    : QObject(parent) {
    try {
        m_db = std::make_unique<PGConnection>(); 
        if (m_db->connection()) {
            qDebug() << "m_db connected successfully";
        } else {
            qDebug() << "Failed to connect m_db";
        }
    } catch (const std::exception& e) {
        qDebug() << "Exception: " << e.what();
    }

    m_query = std::make_unique<Query>(m_db->connection().get());
}

RegHandler::~RegHandler() {}

void RegHandler::regUser(const QString& login, const QString& password) {
    m_user = std::make_unique<User>(login.toStdString(), password.toStdString(), m_query.get());
    m_user->regUser();
}

void RegHandler::loginUser(const QString& login, const QString& password) {
    m_user = std::make_unique<User>(login.toStdString(), password.toStdString(), m_query.get());
    if (m_user->login()) {
        QQmlApplicationEngine *engine = new QQmlApplicationEngine;
        engine->load(QUrl(QStringLiteral("qrc:/ui/newwin.qml")));
    }
}