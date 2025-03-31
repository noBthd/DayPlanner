#include "task.h"
#include "libpq-fe.h"

Task::Task(PGconn* conn, std::string* name, std::string* text) 
    : m_conn(conn), m_task_name(name), m_task_text(text)
{
    // setNewId();
}

Task::~Task() {} 

//? GETTERS ?//

int Task::getID() { return m_id; }

std::string* Task::getTaskName() { return m_task_name; }

std::string* Task::getTaskText() { return m_task_text; }

std::string* Task::getTime() { return m_time;}

bool Task::getDone() { return m_done; }

bool Task::getExpire() { return m_expired; }



//? GETTERS ?//

//==========================//

//? SETTERS ?//

void Task::setID(int id) { m_id = id; }

void Task::setTaskName(std::string* name) { m_task_name = name; }

void Task::setTaskText(std::string* text) { m_task_text = text; }

void Task::setTime(std::string* time) { m_time = time; } 

void Task::setDone(bool done) { m_done = done; }

void Task::setExpired(bool expired) { m_expired = expired; }

//? SETTERS ?//

void Task::done() { m_done = true; }

void Task::expired() { m_expired = true; }

void Task::setNewId() {
    m_id = getPrevId() + 1;
}

int Task::getPrevId() {
    std::string query = "SELECT MAX(task_id) FROM tasks";

    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        qDebug() << "\tFAILED TO GET PREV TASK ID: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return 0;
    }

    if (PQntuples(res) == 0 || PQgetisnull(res, 0, 0)) {
        qDebug() << "No tasks found. TASK_ID = 1";
        m_id = 1;
        PQclear(res);
        return 0;
    }
    
    std::string str_id = PQgetvalue(res, 0, 0);
    int last_id = std::atoi(str_id.c_str());
    PQclear(res);

    return last_id;
}

//! add task uopdating