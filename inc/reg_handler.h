#ifndef REG_HANDLER_H
#define REG_HANDLER_H

#include <QDebug>
#include <QObject>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlProperty>
#include <string>

#include "user.h"
#include "sql/user_query.h"

class RegistrationHandler : public QObject {
        Q_OBJECT
    public:
        explicit RegistrationHandler(QObject* parent = nullptr, Query* = nullptr);

        Q_INVOKABLE User* registrationClick();
        Q_INVOKABLE User* loginClick();

    private:
        std::string m_login;
        std::string m_password;
        Query* m_query;

        void getLoginAndPassword();
};

#endif