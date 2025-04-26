#include "sql/user_query.h"
#include "libpq-fe.h"
#include "utils/passwordUtils.h"
#include <string>

Query::Query(PGconn* conn) {
    m_conn = conn;
};

bool Query::createUser(std::string username, Password password, bool admin) {
    std::string str_admin = admin ? "true" : "false";
    std::string query = "INSERT INTO users(username, password, is_admin) VALUES ('" + username + "', '" + password.hashed_password + "', '" + str_admin + "')";

    if (userExist(username)) {
        qDebug() << "User already exists";
        return false;
    }

    if (!password.isStrong()) {
        qDebug() << "Password isn't strong enough";
        return false;
    }

    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
        qDebug() << "Query failed: " << PQerrorMessage(m_conn);
        PQclear(res);
        return false;
    }

    qDebug() << "User created succesfully";
    PQclear(res);

    return true;
}

std::string Query::getUserPassword(std::string username) {
    std::string query = "SELECT password FROM users WHERE username = '" + username + "';";

    PGresult* res = execQuery(query, PGRES_TUPLES_OK);
    if(!res) return "";

    if (PQntuples(res) == 0) {
        qDebug() << "No user found with username: " << username.c_str();
        PQclear(res);
        return "";
    }

    std::string hash = PQgetvalue(res, 0, 0);
    PQclear(res);

    return hash;
}

//TODO fix query 
PGresult* Query::getUserByID(int id) {
    std::string query = "SELECT * FROM users WHERE id = '" + std::to_string(id) + "';";

    PGresult* res = execQuery(query, PGRES_TUPLES_OK);
    if(!res) return nullptr;

    return res;
}

std::string Query::getUserID(std::string username) {
    std::string query = "SELECT id FROM users WHERE username = '" + username + "';";

    PGresult* res = execQuery(query, PGRES_TUPLES_OK);
    if(!res) return "";

    std::string id = PQgetvalue(res, 0, 0);

    return id;
}

bool Query::userExist(std::string username) {  
    std::string query = "SELECT COUNT(*) FROM users WHERE username = '" + username + "';";

    PGresult* res = execQuery(query, PGRES_TUPLES_OK);
    if(!res) return true;
    
    std::string count = PQgetvalue(res, 0, 0);
    PQclear(res);

    return count != "0";
}

bool Query::isAdmin(std::string username) {
    std::string query = "SELECT is_admin FROM users WHERE username = '" + username + "';";

    PGresult* res = execQuery(query, PGRES_TUPLES_OK);
    if(!res) return false;

    std::string isAdmin = PQgetvalue(res, 0, 0);
    PQclear(res);

    return (isAdmin == "t") ? true : false;
}

int Query::getLastID() {
    std::string query = "SELECT MAX(users.id) from users";
    PGresult* res = execQuery(query, PGRES_TUPLES_OK);
    
    return std::stoi(PQgetvalue(res, 0, 0));
}

PGresult* Query::execQuery(std::string query, ExecStatusType expectedStatus) {
    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != expectedStatus) {
        qDebug() << "Query failed:" << PQerrorMessage(m_conn);
        PQclear(res);
        return nullptr;
    }
    return res;
}

