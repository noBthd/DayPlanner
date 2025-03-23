#include "reg_handler.h"

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
        QObject* rootObject = m_engine->rootObjects().first();
        QQuickWindow* window = qobject_cast<QQuickWindow *>(rootObject);
        if (window) {
            window->hide();
        }

        QQmlComponent component(m_engine, QUrl(QStringLiteral("qrc:/ui/profile.qml")));
        QObject* profileObject = component.create();
        m_profileWindow = qobject_cast<QQuickWindow*>(profileObject);
        if (m_profileWindow) {
            m_profileWindow->show(); 
        }
    }
}

void RegHandler::logoutUser() {
    if (m_user != nullptr) {
        if (m_profileWindow) {
            m_profileWindow->hide();
        }

        QObject* rootObject = m_engine->rootObjects().first();
        QQuickWindow* window = qobject_cast<QQuickWindow *>(rootObject);
        if (window) {
            window->show();
        }
        
        m_user = nullptr;

        qDebug() << "User logged out";
    }
}

QString RegHandler::getQUsername() { return m_user == nullptr ? "" : QString::fromStdString(m_user->getUsername()); }