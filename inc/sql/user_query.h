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
        void createUser(std::string, Password, bool);
        bool userExist(std::string);
        bool isAdmin(std::string);
    private:
        PGconn* m_conn;
};

#endif