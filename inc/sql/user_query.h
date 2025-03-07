#ifndef USER_QUERY_H
#define USER_QUERY_H

#include "sql/pgconn.h"
#include "libpq-fe.h"
#include <libpq-fe.h>
#include <QDebug>
#include <string>

PGresult* getUserByID(PGConnection*, int);
bool userExist(PGconn*, std::string);

#endif