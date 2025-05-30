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
        Q_INVOKABLE void openEditorWin(const int&);
        Q_INVOKABLE void closeEditorWin();

        void insertDBTask(
            std::string,
            std::string,
            std::string
        );
        void removeDBTask(int);
        void editDBTask(
            Task,
            int
        );

        Q_INVOKABLE void delTask(const int&);
        Q_INVOKABLE void addTask(
            const QString&, 
            const QString&, 
            const QString&
        );
        Q_INVOKABLE void editTask(
            const QString&,
            const QString&,
            const QString&
            // const int&
        );
        void getAllUserTasks();

        Q_INVOKABLE LVTask* lvtask() const { return m_lvtask; }

        Q_INVOKABLE void sortByTaksStatus();

        int m_id;
    private: 
        User* m_user; 
        std::vector<Task*>* m_tasks;
        
        PGconn* m_conn;
    
        QQmlApplicationEngine* m_engine;
        QQuickWindow* m_tasksWin; // tasks.qml
        QQuickWindow* m_taskAddWin; // taskAddition.qml
        QQuickWindow* m_taskEditorWin; // taskEditor.qml
        RegHandler* m_rh;
        LVTask* m_lvtask;
};

#endif