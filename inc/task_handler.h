#ifndef TASK_HANDLER_H
#define TASK_HANDLER_H

#include "libpq-fe.h"
#include "task.h"
#include <QObject>
#include <vector>

class TaskHandler : QObject {
    Q_OBJECT;

    public:
        TaskHandler(
            QObject* parent = nullptr, 
            PGconn* conn = nullptr
        );

        ~TaskHandler();

        void addTask(
            QString task_name,
            QString task_text
        );
        void delTask(int task_id);
        void getAllUserTasks(int user_id);

    private: 
        int m_user_id;

        PGconn* m_conn;
        std::vector<Task> m_tasks;
};

#endif