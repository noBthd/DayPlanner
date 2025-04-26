#include "user.h"
#include "sql/user_query.h"
#include "utils/passwordUtils.h"
#include <string>


User::User (std::string username, std::string str_password, Query* query) 
    :m_query(query), m_username(username), m_password(str_password) {
    //TODO fix isn't necessary ->
    if (m_query->userExist(username)) {
        m_id    = std::stoi(m_query->getUserID(username));
        m_admin = m_query->isAdmin(username);
    } else {
        m_id    = m_query->getLastID() + 1;     
        m_admin = false;                        
    }
    //TODO <-
}

void User::getHash() {
    qDebug() << m_password.hashed_password << "\n";
}

bool User::regUser() {
    return m_query->createUser(m_username, m_password, m_admin);
}

bool User::login() {
    if (!m_query->userExist(m_username)) {
        qDebug() << "User does not exists\n";
        return false;
    }

    std::string storedHash = m_query->getUserPassword(m_username);

    if (m_password.hashed_password != storedHash) {
        qDebug() << "Password isn't right\n";
        return false;
    } 

    m_admin = isAdmin();
    if (m_admin) {
        qDebug() << "\tUSER IS ADMIN";
    }

    m_id = std::stoi(m_query->getUserID(m_username));
    qDebug() << "\tUSER LOGGED IN AS " << m_username  << "\tUSER ID: " << std::stoi(m_query->getUserID(m_username)) << "\n";
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

int User::getID() {
    return m_id;
}