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

        std::string getUserID(const std::string&);
        std::string getUserPassword(const std::string&);
        PGresult* getUserByID(int);
        bool createUser(const std::string&, Password, bool);
        bool userExist(const std::string&);
        bool isAdmin(const std::string&);
        int getLastID();
    private:
        PGresult* execQuery(const std::string&, ExecStatusType);
        PGconn* m_conn;
};

#endif