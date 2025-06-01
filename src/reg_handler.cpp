#include "reg_handler.h"

RegHandler::RegHandler(QQmlApplicationEngine* engine, PGconn* conn, QObject* parent) 
    : QObject(parent), m_engine(engine) {
    m_query = std::make_unique<Query>(conn);

}

RegHandler::~RegHandler() {}

void RegHandler::regUser(const QString& login, const QString& password) {
    m_user = std::make_unique<User>(login.toStdString(), password.toStdString(), m_query.get());

    if (m_user->regUser()) {
        QObject* rootObject = m_engine->rootObjects().first();
        QQuickWindow* window = qobject_cast<QQuickWindow *>(rootObject);
        if (window) {
            window->hide();
        }

        QQmlComponent component(m_engine, QUrl(QStringLiteral("qrc:/ui/tasks.qml")));
        if (component.status() != QQmlComponent::Ready) {
            qDebug() << "COMPONENT LOAD ERR: " << component.errorString();
            return;
        }

        QObject* profileObject = component.create();
        if (!profileObject) {
            qDebug() << "FAILED TO CREATE COMPONENT";
            return;
        }

        m_profileWindow = qobject_cast<QQuickWindow*>(profileObject);
        if (!m_profileWindow) {
            qDebug() << "COMPONENT ISN'T A WINDOW";
            delete profileObject;
            return;
        }
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

        QQmlComponent component(m_engine, QUrl(QStringLiteral("qrc:/ui/tasks.qml")));
        if (component.status() != QQmlComponent::Ready) {
            qDebug() << "COMPONENT LOAD ERR: " << component.errorString();
            return;
        }

        QObject* profileObject = component.create();
        if (!profileObject) {
            qDebug() << "FAILED TO CREATE COMPONENT";
            return;
        }

        m_profileWindow = qobject_cast<QQuickWindow*>(profileObject);
        if (!m_profileWindow) {
            qDebug() << "COMPONENT ISN'T A WINDOW";
            delete profileObject;
            return;
        }

        m_engine->rootContext()->setContextProperty("isAdmin", m_user->isAdmin());
    }
}

void RegHandler::logoutUser() {
    if (m_user != nullptr) {
        if (m_profileWindow) {
            m_profileWindow->hide();
        }

        QObject* rootObject = m_engine->rootObjects().first();
        QQuickWindow* window = qobject_cast<QQuickWindow*>(rootObject);
        if (window) {
            window->show();
        }
        
        m_user = nullptr;

        qDebug() << "User logged out";
    }
}

QString RegHandler::getQUsername() { return m_user == nullptr ? "" : QString::fromStdString(m_user->getUsername()); }

User* RegHandler::getUser() { return m_user.get(); }

QQuickWindow* RegHandler::getWin() { //? tmp
    return m_profileWindow; 
};

void RegHandler::reloadWindow() {
    if (m_profileWindow) {
        m_profileWindow->close();
        m_profileWindow->show();
        qDebug() << "-=-=-<=WINDOW RELOADED=>-=-=-";
    }
}