#ifndef REG_HANDLER_H
#define REG_HANDLER_H

#include <QDebug>
#include <QObject>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlProperty>
#include <QQmlApplicationEngine>
#include <memory>

#include "sql/user_query.h"
#include "user.h"
#include "sql/pgconn.h"

class RegHandler : public QObject {
        Q_OBJECT
    public:
        explicit RegHandler(QQmlApplicationEngine* = nullptr, QObject* parent = nullptr); 
        ~RegHandler();
        
        Q_INVOKABLE void regUser(const QString&, const QString&);
        Q_INVOKABLE void loginUser(const QString&, const QString&);

    private:
        QQmlApplicationEngine* m_engine;
        std::unique_ptr<User> m_user;
        std::unique_ptr<Query> m_query;
        std::unique_ptr<PGConnection> m_db;

    signals:
                
};

#endif