#ifndef USER_H
#define USER_H

#include <string>
#include <QByteArray>

class User {
    public:
        User();
    private:
        std::string m_username;
        QByteArray m_password;
};

#endif