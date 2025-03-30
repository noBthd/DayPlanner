#include "task_handler.h"

TaskHandler::TaskHandler(QQmlApplicationEngine* engine, PGconn* conn, RegHandler* rh, QObject* parent) //? tmp
    : m_conn(conn), m_engine(engine), m_rh(rh), QObject(parent)
{
    
}

TaskHandler::~TaskHandler() {};

void TaskHandler::openAdditionWin() {
    if (!m_taskAddWin) {
        QQmlComponent component(m_engine, QUrl(QStringLiteral("qrc:/ui/taskAddition.qml")));
        QObject* m_object = component.create();
        m_taskAddWin = qobject_cast<QQuickWindow*>(m_object);
    }
    if (m_taskAddWin) {
        m_taskAddWin->show(); 
    }
}

void TaskHandler::closeAdditionWin() {
    m_taskAddWin->hide();
}

void TaskHandler::addTask(const QString& task_name, const QString& task_text) {
}

void TaskHandler::delTask(const int& task_id) {
    qDebug() << "\tREG HANDLER: " << m_rh->getWin();
    m_tasksWin = m_rh->getWin();

    if (task_id == -1) {
        qDebug() << "NO TASK CHOOSEN";
        return;
    }
    qDebug() << "\tTASK INDEX: " << task_id;
}

void TaskHandler::getAllUserTasks(int user_id) {

}

//! add setting task on loading ui
