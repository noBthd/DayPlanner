#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <QCryptographicHash>
#include <string>

class Password {
    public:
        Password(std::string);

        QByteArray hashed_password;

        bool isStrong();

    private:
        std::string m_password;
        int hasDigit(std::string);
        void hashPassword(std::string);
};

#endif