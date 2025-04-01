#include "task_handler.h"
#include "libpq-fe.h"
#include "task.h"
#include <string>
#include <vector>

TaskHandler::TaskHandler(QQmlApplicationEngine* engine, PGconn* conn, RegHandler* rh, QObject* parent) //? tmp
    : m_conn(conn), m_engine(engine), m_rh(rh), QObject(parent)
{
    m_tasks = new std::vector<Task>;
}

TaskHandler::~TaskHandler() {};

//? SETTING USER ON LOAD
void TaskHandler::setUser() { 
    m_user = m_rh->getUser();
    qDebug() << "USER DATA LOADED: " << m_user->getID();
    getAllUserTasks();
}

//? user data clear on close


void TaskHandler::openAdditionWin() {
    if (!m_taskAddWin) {
        QQmlComponent component(m_engine, QUrl(QStringLiteral("qrc:/ui/taskAddition.qml")));
        QObject* m_object = component.create();
        m_taskAddWin = qobject_cast<QQuickWindow*>(m_object);
    }
    if (m_taskAddWin) {
        m_taskAddWin->show(); 
    }

    std::string test1 = "test";
    std::string test2 = "yesy dqdasdasd";
    insertTask(QString::fromStdString(test1), QString::fromStdString(test1));
}

void TaskHandler::closeAdditionWin() {
    m_taskAddWin->hide();
}

//! add inserting time done expired;
//? db adding/removing task
void TaskHandler::insertTask(const QString& task_name, const QString& task_text) {
    std::string id = std::to_string(m_user->getID());
    std::string query = "INSERT INTO tasks(user_id, task_name,task_text, expire_time, is_done, is_expired) VALUES (" 
        + id + ", '" + task_name.toStdString() + "', '" + task_text.toStdString() + "', '00:00:00', 't', 'f')";
    
    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        qDebug() << "\n\tFAILED TO INSERT TASK: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return;
    }

    PQclear(res);
    qDebug() << "\tTASK INSERTED\n";
}

void TaskHandler::removeTask(int task_id) {

}
//? db adding/removing task

void TaskHandler::delTask(const int& task_id) {
    qDebug() << "\tREG HANDLER: " << m_rh->getWin();
    m_tasksWin = m_rh->getWin();

    if (task_id == -1) {
        qDebug() << "NO TASK CHOOSEN";
        return;
    }
    qDebug() << "\tTASK INDEX: " << task_id; //? DEBUG
}

void TaskHandler::getAllUserTasks() {
    std::string query = "SELECT * FROM tasks WHERE user_id = '" + std::to_string(m_user->getID()) + "';"; 

    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        qDebug() << "FAILED TO GET TASKS: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return;
    }

    if (PQntuples(res) == 0) {
        qDebug() << "No user tasks found\n\t USER: " << m_rh->getQUsername();
        PQclear(res);
        return;
    }
    
    int nRows = PQntuples(res);  
    if (m_tasks)
    {    
        for (int row = 0; row < nRows; row++) {
            Task task;
            std::string* t_name = new std::string;
            *t_name = std::string(PQgetvalue(res, row, 2));
            std::string* t_text = new std::string;
            *t_text = std::string(PQgetvalue(res, row, 3));
            std::string* t_time = new std::string;
            *t_time = std::string(PQgetvalue(res, row, 4));

            task.setID(std::stoi(PQgetvalue(res, row, 0)));
            task.setTaskName(t_name);
            task.setTaskText(t_text);

            task.setTime(t_time); 
            bool tmp = (std::string(PQgetvalue(res, row, 5)) == "t") ? true : false;
            task.setDone(tmp);
            tmp = (std::string(PQgetvalue(res, row, 6)) == "t") ? true : false;
            task.setExpired(tmp);

            m_tasks->push_back(task);
        }
    }

    //? DEBUG ?//
    for (Task task : *m_tasks) {
        // Task task = m_tasks->back();
        qDebug() << "\tTASK ID: "<< task.getID() 
        << "\n\tTASK NAME: " << QString::fromUtf8(task.getTaskName()->c_str())
        << "\n\tTASK TEXT: " << QString::fromUtf8(task.getTaskText()->c_str())
        << "\n\tTASK TIME" << QString::fromUtf8(task.getTime()->c_str())
        << "\n\tTASK DONE: " << task.getDone()
        << "\n\tTASK EPIRED" << task.getExpire() << "\n";
    }

    PQclear(res);
}

//! add setting task on loading ui
