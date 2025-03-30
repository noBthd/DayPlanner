#include "task_handler.h"

TaskHandler::TaskHandler(QQmlApplicationEngine* engine, PGconn* conn, QObject* parent) 
    : m_conn(conn), m_engine(engine), QObject(parent)
{
}

TaskHandler::~TaskHandler() {};

void TaskHandler::openAdditionWin() {
    if (!m_taskAddWin) {
        QQmlComponent component(m_engine, QUrl(QStringLiteral("qrc:/ui/taskAddition.qml")));
        QObject* m_object = component.create();
        m_taskAddWin = qobject_cast<QQuickWindow*>(m_object);
    }
    if (m_taskAddWin) {
        m_taskAddWin->show(); 
    }
}

void TaskHandler::closeAdditionWin() {
    m_taskAddWin->close();
}

void TaskHandler::addTask(QString task_name, QString task_text) {
    
}

void TaskHandler::delTask(int task_id) {

}

void TaskHandler::getAllUserTasks(int user_id) {

}

//! add setting task on loading ui
