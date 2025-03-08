#include "user.h"
#include "sql/user_query.h"
#include "utils/passwordUtils.h"
#include <string>


User::User (std::string username, std::string str_password, Query* query) 
    :m_query(query), m_username(username), m_password(str_password) {

    if (m_query->userExist(username)) {
        m_id    = std::stoi(m_query->getUserID(username));
        m_admin = m_query->isAdmin(username);
    } else {
        m_id    = -1;
        m_admin = false;
    }
}

bool User::regUser() {
    m_query->createUser(m_username, m_password, m_admin);
    return false;
}

void User::getHash() {
    qDebug() << m_password.hashed_password << "\n";
}

bool User::login() {
    if (!m_query->userExist(m_username)) {
        qDebug() << "User does not exists\n";
        return false;
    }

    QByteArray storedHash = m_query->getUserPassword(m_username);
    qDebug() << "STORED HASH: " << storedHash << "\n";
    qDebug() << "PASSWORD HASH: " << m_password.hashed_password << "\n";

    if (m_password.hashed_password != storedHash) {
        qDebug() << "Password isn't right\n";
        return false;
    } 

    qDebug() << "User logged in\n";
    return true;
}

bool User::exists() {
    return m_query->userExist(m_username);
}

bool User::isAdmin() {
    return m_query->isAdmin(m_username);
}

std::string User::getUsername() {
    return m_username;
}
