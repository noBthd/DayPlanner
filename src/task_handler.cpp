#include "task_handler.h"
#include "libpq-fe.h"
#include "task.h"
#include <string>
#include <vector>

TaskHandler::TaskHandler(QQmlApplicationEngine* engine, PGconn* conn, RegHandler* rh, QObject* parent) //? tmp
    : m_conn(conn), m_engine(engine), m_rh(rh), QObject(parent)
{
    m_tasks = new std::vector<Task*>;
    m_lvtask = new LVTask(this);
    m_lvtask->clear();
}

TaskHandler::~TaskHandler() {};

//? SETTING USER ON LOAD
void TaskHandler::setUser() { 
    m_user = m_rh->getUser();
    qDebug() << "USER DATA LOADED: " << m_user->getID();
    getAllUserTasks();
}

//? user data clear on close
void TaskHandler::clearUser() {
    m_user = nullptr;

    m_tasks->clear();
    m_lvtask->clear();
}

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

//TODO: add inserting time done expired;
//? db adding/removing task
void TaskHandler::insertDBTask(std::string task_name, std::string task_text, std::string task_status) {
    std::string id = std::to_string(m_user->getID());

    std::string query = "INSERT INTO tasks(user_id, task_name, task_text, expire_time, is_expired, status) VALUES (" + id + ", '" + task_name + "', '" + task_text + "', '13:13:13', 't', '" + task_status + "')";
    
    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        qDebug() << "\n\tFAILED TO INSERT THE TASK: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return;
    }

    PQclear(res);
    qDebug() << "\tTASK INSERTED\n";
}

void TaskHandler::removeDBTask(int task_id) {
    std::string query = "DELETE FROM tasks WHERE task_id = " + std::to_string(task_id) + "";

    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        qDebug() << "\n\tFAILED TO DELETE THE TASK: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return;
    }

    PQclear(res);
    qDebug() << "\n\tTASK DELETED FROM DB";
}

//? qml adding/removing 
//TODO fix (if task plate outside of the view u'll get error:)
//! libc++abi: terminating due to uncaught exception of type std::out_of_range: vector
//! [1]    89411 abort      ./DayPlanner
void TaskHandler::delTask(const int& task_id) {
    qDebug() << "\tREG HANDLER: " << m_rh->getWin();
    m_tasksWin = m_rh->getWin();

    if (task_id == -1) {
        qDebug() << "\nNO TASK CHOOSEN";
        return;
    }

    if (task_id >= m_lvtask->rowCount() || task_id < 0 || task_id >= m_tasks->size()) {
        qDebug() << "\nNO TASK CHOOSEN (out of index)";
        return;
    }

    //? DEBUG ?//
    qDebug() << "\tTASK INDEX: " << task_id << "\n"; 
    qDebug() << "\tTASK DB_INDEX: " << m_tasks->at(task_id)->getID();
    qDebug() << "\tROWS: " << m_lvtask->rowCount();

    removeDBTask(m_tasks->at(task_id)->getID());
    m_lvtask->removeTask(task_id);
}

void TaskHandler::addTask(const QString& t_qname, const QString& t_qstatus, const QString& t_qtext) {
    std::string* t_name = new std::string(t_qname.toStdString());
    std::string* t_text = new std::string(t_qtext.toStdString());
    std::string* t_status = new std::string(t_qstatus.toStdString());

    insertDBTask(*t_name, *t_text, *t_status);

    Task* task = new Task();
    task->setTaskName(t_name);
    task->setTaskText(t_text);
    task->setStatus(t_status);

    m_lvtask->addTask(task);
    qDebug() << "\n\tTASK ADDED FOR USER: " << m_user->getID();
}

void TaskHandler::getAllUserTasks() {
    std::string query = "SELECT * FROM tasks WHERE user_id = '" + std::to_string(m_user->getID()) + "';"; 

    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        qDebug() << "\nFAILED TO GET TASKS: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return;
    }

    if (PQntuples(res) == 0) {
        qDebug() << "No user tasks found\n\t USER: " << m_rh->getQUsername();
        PQclear(res);
        return;
    }
    
    int nRows = PQntuples(res);  
    if (m_tasks) {    
        for (int row = 0; row < nRows; row++) {
            Task* task = new Task(); 
        
            std::string* t_name = new std::string(PQgetvalue(res, row, 2));
            std::string* t_text = new std::string(PQgetvalue(res, row, 3));
            std::string* t_time = new std::string(PQgetvalue(res, row, 4));
            std::string* t_status = new std::string(PQgetvalue(res, row, 6));
        
            task->setID(std::stoi(PQgetvalue(res, row, 0)));
            task->setTaskName(t_name);
            task->setTaskText(t_text);
            task->setStatus(t_status);
            task->setTime(t_time);

            bool tmp = (std::string(PQgetvalue(res, row, 5)) == "t");
            task->setExpired(tmp);
        
            m_tasks->push_back(task);  
            if(m_lvtask) {
                qDebug() << "M_LVTASK ADDED: " << task;
                m_lvtask->addTask(task);        
            }
        }
    }

    //? DEBUG ?//
    qDebug() << "\nTASKS:";
    for (Task* task : *m_tasks) {
        qDebug() << "\n\tTASK ID: "<< task->getID() 
        << "\n\tTASK NAME: " << QString::fromUtf8(task->getTaskName()->c_str())
        << "\n\tTASK TEXT: " << QString::fromUtf8(task->getTaskText()->c_str())
        << "\n\tTASK TIME" << QString::fromUtf8(task->getTime()->c_str())
        << "\n\tTASK STATUS: " << QString::fromUtf8(task->getStatus()->c_str())
        << "\n\tTASK EPIRED" << task->getExpire() << "\n";
    }

    PQclear(res);
}

//? test
// void TaskHandler::setPickedID(const int& id) {
//     m_id = id;
//     qDebug() << "ID SETTED: " << m_id;
// }
// TEST