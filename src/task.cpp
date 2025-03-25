#include "task.h"
#include <cstddef>

Task::Task(std::string* name, std::string* text) 
    : m_task_name(*name), m_task_text(*text), m_done(false), m_expidred(false)
{
    try {
        m_db = new PGConnection(); 
        if (m_db->connection()) {
            qDebug() << "m_db connected successfully";
        } else {
            qDebug() << "Failed to connect m_db";
        }
    } catch (const std::exception& e) {
        qDebug() << "Exception: " << e.what();
    }
}

Task::~Task() {} 

std::string Task::getTaskName() { return m_task_name; }

std::string Task::getTaskText() { return m_task_text; }

bool Task::getDone() { return m_done; }

bool Task::getExpire() { return m_expidred; }

void Task::setTaskName(std::string name) { m_task_name = name; }

void Task::setTaskText(std::string text) { m_task_text = text; }

void Task::done() { m_done = true; }

void Task::expired() { m_expidred = true; }

// void Task::setNewId() {
//     m_id = 
// }

// int Task::getPrevId() {
//     std::string query = "SELECT password FROM users WHERE username = '" + username + "';";

//     PGresult* res = PQexec(m_conn, query.c_str());
//     if (PQresultStatus(res) != PGRES_TUPLES_OK) {
//         qDebug() << "Query failed: " << PQerrorMessage(m_conn) << "\n";
//         PQclear(res);
//         return 0;
//     }

//     if (PQntuples(res) == 0) {
//         PQclear(res);
//     }

//     int last_id = PQgetvalue(res, 0, 0);
//     PQclear(res);

//     return last_id;
// }