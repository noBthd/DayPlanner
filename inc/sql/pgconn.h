#ifndef PGCONNECTION_H
#define PGCONNECTION_H

#include <libpq-fe.h>
#include <string>

class PGConnection {
public:
    PGConnection();
    std::shared_ptr<PGconn> connection() const;

private:
    void establish_connection();

    std::string m_dbhost = "localhost";
    int         m_dbport = 5432;
    std::string m_dbname = "ToDoAppDB";
    std::string m_dbuser = "postgres";
    std::string m_dbpass = "1234";

    std::shared_ptr<PGconn>  m_connection;
    
};

#endif