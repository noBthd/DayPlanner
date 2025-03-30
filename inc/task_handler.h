#ifndef TASK_HANDLER_H
#define TASK_HANDLER_H

#include "libpq-fe.h"
#include "task.h"
#include <QObject>
#include <QQuickView>
#include <QQmlProperty>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

class TaskHandler : public QObject {
    Q_OBJECT;

    public:
        TaskHandler(
            QQmlApplicationEngine* engine = nullptr,
            PGconn* conn = nullptr,
            QObject* parent = nullptr
        );

        ~TaskHandler();

        Q_INVOKABLE void openAdditionWin();
        Q_INVOKABLE void closeAdditionWin();

        void addTask(
            QString task_name,
            QString task_text
        );
        void delTask(int task_id);
        void getAllUserTasks(int user_id);

    private: 
        int m_user_id;

        std::vector<Task> m_tasks;

        PGconn* m_conn;
        QQuickWindow* m_taskAddWin;
        QQmlApplicationEngine* m_engine;
};

#endif