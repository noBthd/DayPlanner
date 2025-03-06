#include "passwordUtils.h"

// password strongness checker
bool isStrong(std::string password) {

    return false;
}

// password hash func
QByteArray hashPassword(std::string password) {
    // hashing and returning password with Md5 method
    return QCryptographicHash::hash(password, QCryptographicHash::Md5);
} 