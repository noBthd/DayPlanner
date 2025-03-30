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
        explicit TaskHandler(
            QQmlApplicationEngine* engine = nullptr,
            PGconn* conn = nullptr,
            QQuickWindow* win = nullptr,
            QObject* parent = nullptr
        );

        ~TaskHandler();

        Q_INVOKABLE void openAdditionWin();
        Q_INVOKABLE void closeAdditionWin();

        Q_INVOKABLE void addTask(
            const QString& task_name,
            const QString& task_text
        );
        Q_INVOKABLE void delTask(const int& task_id);
        void getAllUserTasks(int user_id);

    private: 
        int m_user_id;

        std::vector<Task> m_tasks;

        PGconn* m_conn;
        QQmlApplicationEngine* m_engine;
        QQuickWindow* m_tasksWin; // tasks.qml
        QQuickWindow* m_taskAddWin; // taskAddition.qml
};

#endif