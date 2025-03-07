#include "sql/user_query.h"
#include "libpq-fe.h"
#include <string>

PGresult* getUserByID(PGconn* conn, int id) {
    std::string query = "SELECT COUNT(*) FROM users WHERE username = '" + std::to_string(id) + "';";
    
    PGresult* res = PQexec(conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        qDebug() << "Query failed: " << PQerrorMessage(conn) << "\n";
        PQclear(res);
        return nullptr;
    }

    return res;
}

bool userExist(PGconn* conn, std::string username) {  
    std::string query = "SELECT COUNT(*) FROM users WHERE username = '" + username + "';";

    PGresult* res = PQexec(conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        qDebug() << "Query failed: " << PQerrorMessage(conn) << "\n";
        PQclear(res);
        return true;
    }
    
    std::string count = PQgetvalue(res, 0, 0);
    PQclear(res);

    return count != "0";
}