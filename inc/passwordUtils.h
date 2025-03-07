#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <QCryptographicHash>
#include <string>

class Password {
    public:
        Password(std::string);
        const QByteArray password;
        void hashPassword(std::string);
        bool isStrong(std::string);

    private:
        int hasDigit(std::string);
        std::string m_password;
};

#endif