#ifndef TASK_HANDLER_H
#define TASK_HANDLER_H

#include "libpq-fe.h"
#include "reg_handler.h"
#include "task.h"
#include <vector>
#include <QObject>
#include <QQuickView>
#include <QQmlProperty>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QListView>
#include <QAbstractListModel>
#include <QVariant>

class TaskHandler : public QObject {
    Q_OBJECT;

    public:
        explicit TaskHandler(
            QQmlApplicationEngine* engine = nullptr,
            PGconn* conn = nullptr,
            RegHandler* rh = nullptr,
            QObject* parent = nullptr
        );

        ~TaskHandler();

        Q_INVOKABLE void setUser();
        Q_INVOKABLE void clearUser();

        Q_INVOKABLE void openAdditionWin();
        Q_INVOKABLE void closeAdditionWin();

        Q_INVOKABLE void insertTask(
            const QString&,
            const QString&
        );
        void removeTask(int);

        Q_INVOKABLE void delTask(const int&);
        void getAllUserTasks();

    private: 
        User* m_user;
        std::vector<Task>* m_tasks;
    
        PGconn* m_conn;
    
        QQmlApplicationEngine* m_engine;
        QQuickWindow* m_tasksWin; // tasks.qml
        QQuickWindow* m_taskAddWin; // taskAddition.qml
        RegHandler* m_rh;
};

#endif