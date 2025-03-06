#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <QCryptographicHash>

bool isStrong(std::string);
QByteArray hashPassword(std::string);

#endif