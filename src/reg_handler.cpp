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
        QObject *rootObject = m_engine->rootObjects().first();
        QQuickWindow *window = qobject_cast<QQuickWindow *>(rootObject);

        if (window) {
            window->close();
        }
        m_engine->load(QUrl(QStringLiteral("qrc:/ui/profile.qml")));
    }
}

void RegHandler::loginUser(const QString& login, const QString& password) {
    m_user = std::make_unique<User>(login.toStdString(), password.toStdString(), m_query.get());

    if (m_user->login()) {
        QObject *rootObject = m_engine->rootObjects().first();
        qDebug() << rootObject;
        QQuickWindow *window = qobject_cast<QQuickWindow *>(rootObject);

        if (window) {
            window->close();
        }

        m_engine->load(QUrl(QStringLiteral("qrc:/ui/profile.qml")));

        rootObject = m_engine->rootObjects().first();
        window = qobject_cast<QQuickWindow *>(rootObject);

        if (window) {
            qDebug() << rootObject;
        }
    }
}

void RegHandler::logoutUser() {
    if (m_user != nullptr) {
        QObject *rootObject = m_engine->rootObjects().first();
        qDebug() << rootObject;
        QQuickWindow *window = qobject_cast<QQuickWindow *>(rootObject);
        
        if (window) {
            window->close();
            qDebug() << "Window closed!";
        }
        
        m_engine->load(QUrl(QStringLiteral("qrc:/ui/login.qml")));

        qDebug() << m_user->getUsername() << "\n" << m_user->isAdmin() << "\n";

        m_user = nullptr;
    }
}

QString RegHandler::getQUsername() { return m_user == nullptr ? "" : QString::fromStdString(m_user->getUsername()); }