#include "task_handler.h"

TaskHandler::TaskHandler(QObject* parent, PGconn* conn) 
    : QObject(parent), m_conn(conn)
{

}

TaskHandler::~TaskHandler() {};

void TaskHandler::addTask(QString task_name, QString task_text) {
    
}

void TaskHandler::delTask(int task_id) {

}

void TaskHandler::getAllUserTasks(int user_id) {

}

//! add setting task on loading ui
