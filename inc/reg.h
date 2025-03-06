#ifndef REG_H
#define REG_H

#include <libpq-fe.h>
#include <string>
#include <QDebug>

bool userExist(PGconn*, std::string);

#endif