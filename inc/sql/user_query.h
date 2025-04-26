#ifndef USER_QUERY_H
#define USER_QUERY_H

#include "libpq-fe.h"
#include "utils/passwordUtils.h"
#include <libpq-fe.h>
#include <QDebug>
#include <string>

class Query {
    public:
        Query(PGconn*);

        std::string getUserID(std::string);
        std::string getUserPassword(std::string);
        PGresult* getUserByID(int);
        bool createUser(std::string, Password, bool);
        bool userExist(std::string);
        bool isAdmin(std::string);
        int getLastID();
    private:
        PGresult* execQuery(std::string, ExecStatusType);
        PGconn* m_conn;
};

#endif