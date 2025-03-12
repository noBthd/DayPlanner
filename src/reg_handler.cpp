#include "reg_handler.h"

RegistrationHandler::RegistrationHandler(QObject* parent, Query* query) 
    : QObject(parent), m_query(query) {

}

void RegistrationHandler::getLoginAndPassword() {
    QQuickView view;
    view.setSource(QUrl(QStringLiteral("qrc:/ui/components/Reg.qml")));
    QObject* object = view.rootObject();
    
    QObject* obj_login = object->findChild<QObject*>("loginInput");
    QObject* obj_password = object->findChild<QObject*>("passwordInput");
    if (!obj_login || !obj_password) {
        qDebug() << "Failed to find object";
        return;
    }
    
    
    m_login = obj_login->property("text").toString().toStdString();
    m_password = obj_password->property("text").toString().toStdString();  
}

User* RegistrationHandler::registrationClick() {
    getLoginAndPassword();
    User* user = new User(m_login, m_password, m_query);
    user->login();

    return user;
}

User* RegistrationHandler::loginClick() {
    getLoginAndPassword();
    User* user = new User(m_login, m_password, m_query);
    user->regUser();

    return user;
}
