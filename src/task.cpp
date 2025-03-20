#include "task.h"

Task::Task(std::string* name, std::string* text) 
    : m_task_name(*name), m_task_text(*text)
{

}

Task::~Task() {} 

std::string Task::getTaskName() { return m_task_name; }

std::string Task::getTaskText() { return m_task_text; }

bool Task::getDone() { return m_done; }

bool Task::getExpire() { return m_expidred; }

bool Task::setTaskName(std::string name) { 
    m_task_name = name;
    return true;
}

bool Task::setTaskText(std::string text) {
    m_task_text = text;
    return true;
}

void Task::done() { m_done = true; }

void Task::expired() { m_expidred = true; }
