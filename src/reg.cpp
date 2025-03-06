#include "reg.h"
#include "libpq-fe.h"

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