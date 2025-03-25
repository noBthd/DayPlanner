#ifndef TASK_HANDLER_H
#define TASK_HANDLER_H

#include "task.h"
#include <QObject>
#include <vector>

class TaskHandler : QObject {
    Q_OBJECT;

    public:
        TaskHandler(QObject* parent = nullptr);
        ~TaskHandler();

        void addTask(Task task);
        void delTask(int task_id);
        std::vector<Task> getAllUserTasks(int user_id);

    private: 
        int m_user_id;
        std::vector<Task> m_tasks;
};

#endif