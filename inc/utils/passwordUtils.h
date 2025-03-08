#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <QCryptographicHash>
#include <string>

class Password {
    public:
        Password(std::string);

        std::string hashed_password;
        std::string m_password;

        bool isStrong();

    private:
        int hasDigit(std::string);
        void hashPassword(std::string);
};

#endif