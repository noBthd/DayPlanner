#include "task.h"
#include <string>

Task::Task() {}

Task::~Task() {} 

std::string Task::getTaskName() { return m_task_name; }

std::string Task::getTaskText() { return m_task_text; }
