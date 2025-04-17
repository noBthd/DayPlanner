#ifndef TASK_HANDLER_H
#define TASK_HANDLER_H

#include "lv_tasks_model.h"
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
        Q_INVOKABLE void removeDBTask(int);

        Q_INVOKABLE void delTask(const int&);
        void getAllUserTasks();

        Q_INVOKABLE LVTask* lvtask() const { return m_lvtask; }

    private: 
        User* m_user; 
        std::vector<Task*>* m_tasks;
        
        PGconn* m_conn;
    
        QQmlApplicationEngine* m_engine;
        QQuickWindow* m_tasksWin; // tasks.qml
        QQuickWindow* m_taskAddWin; // taskAddition.qml
        RegHandler* m_rh;
        LVTask* m_lvtask;
};

#endif