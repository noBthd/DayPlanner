#include "utils/passwordUtils.h"
#include <cctype>
#include <string>

Password::Password(std::string password) 
    : m_password(password) {

    hashPassword(password);
}

// password strongness checker
bool Password::isStrong() {
    if (
        m_password.length() >= 8 &&
        hasDigit(m_password) >= 4
    ) {
        return true;
    }

    return false;
}

// checking for digits and returning count of 
int Password::hasDigit(std::string password) {
    int counter = 0;

    for(char c : password) {
        if (isdigit(c)) {
            counter++;
        }
    }
    return counter;
}

// password hash func
void Password::hashPassword(std::string password) {
    // hashing and returning password with Md5 method
    hashed_password = QCryptographicHash::hash(QByteArray::fromStdString(password), QCryptographicHash::Md5).toHex();
} 