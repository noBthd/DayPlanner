#ifndef TASK_HANDLER_H
#define TASK_HANDLER_H

#include <QObject>

class TaskHandler : QObject {
    Q_OBJECT;

    public:
        TaskHandler(QObject* parent = nullptr);
        ~TaskHandler();

    private: 
};

#endif