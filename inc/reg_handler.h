#ifndef REG_HANDLER_H
#define REG_HANDLER_H

#include <QDebug>
#include <QObject>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlProperty>
#include <QQmlApplicationEngine>
#include <memory>
#include <QString>
#include <QQmlContext>

#include "libpq-fe.h"
#include "sql/user_query.h"
#include "user.h"

class RegHandler : public QObject {
        Q_OBJECT
    public:
        explicit RegHandler(QQmlApplicationEngine* = nullptr, PGconn* conn = nullptr, QObject* parent = nullptr); 
        ~RegHandler();
        
        Q_INVOKABLE void regUser(const QString&, const QString&);
        Q_INVOKABLE void loginUser(const QString&, const QString&);
        Q_INVOKABLE void logoutUser();
        Q_INVOKABLE QString getQUsername();
        User* getUser();
        QQuickWindow* getWin();
        Q_INVOKABLE void reloadWindow();
        
    private:
        QQmlApplicationEngine* m_engine;
        QQuickWindow* m_profileWindow;
        std::unique_ptr<User> m_user;
        std::unique_ptr<Query> m_query;

    signals:

};

#endif