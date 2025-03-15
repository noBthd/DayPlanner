#include "reg_handler.h"
#include "sql/pgconn.h"
#include "sql/user_query.h"

RegHandler::RegHandler(QQmlApplicationEngine* engine, QObject* parent) 
    : QObject(parent), m_engine(engine) {
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
    if (m_user->regUser()) {
        // m_engine->load(QUrl(QStringLiteral("qrc:/ui/newwin.qml")));
        emit changePage("qrc:/ui/newwin.qml");
    }
}

void RegHandler::loginUser(const QString& login, const QString& password) {
    m_user = std::make_unique<User>(login.toStdString(), password.toStdString(), m_query.get());
    if (m_user->login()) {
        // m_engine->load(QUrl(QStringLiteral("qrc:/ui/newwin.qml")));
        emit changePage("qrc:/ui/newwin.qml");
    }
}
