#include "task_handler.h"
#include "libpq-fe.h"
#include <cstdio>
#include <cstring>
#include <string>

TaskHandler::TaskHandler(QQmlApplicationEngine* engine, PGconn* conn, RegHandler* rh, QObject* parent) //? tmp
    : m_conn(conn), m_engine(engine), m_rh(rh), QObject(parent)
{
    m_user = m_rh->getUser();
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
    m_taskAddWin->hide();
}

void TaskHandler::addTask(const QString& task_name, const QString& task_text) {

}

void TaskHandler::delTask(const int& task_id) {
    qDebug() << "\tREG HANDLER: " << m_rh->getWin();
    m_tasksWin = m_rh->getWin();

    if (task_id == -1) {
        qDebug() << "NO TASK CHOOSEN";
        return;
    }
    qDebug() << "\tTASK INDEX: " << task_id;
}

void TaskHandler::getAllUserTasks() {
    std::string query = "SELECT * FROM tasks WHERE user_id = '" + std::to_string(m_user->getID()) + "';"; 

    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        qDebug() << "Query failed: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return;
    }

    if (PQntuples(res) == 0) {
        qDebug() << "No user tasks found\n USER: " << m_rh->getQUsername();
        PQclear(res);
        return;
    }
    
    Task* task;
    int nRows = PQntuples(res);  
    for (int row = 0; row < nRows; row++) {
        task->setID(std::stoi(PQgetvalue(res, row, 0)));
        task->setTaskName(PQgetvalue(res, row, 2));
        task->setTaskText(PQgetvalue(res, row, 3));
        task->setTime(PQgetvalue(res, row, 4));
        bool tmp = (std::string(PQgetvalue(res, row, 5)) == "t") ? true : false;
        task->setDone(tmp);
        tmp = (std::string(PQgetvalue(res, row, 6)) == "t") ? true : false;
        task->setExpired(tmp);
    }
    
    PQclear(res);
}

//! add setting task on loading ui
