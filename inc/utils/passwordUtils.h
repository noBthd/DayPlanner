#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <QCryptographicHash>
#include <string>

class Password {
    public:
        Password(std::string);
        const QByteArray password;
        bool isStrong(std::string);

    private:
        void hashPassword(std::string);
        int hasDigit(std::string);
        std::string m_password;
};

#endif