#include "task_handler.h"
#include "libpq-fe.h"
#include "task.h"
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <QFile>
#include <QDir>

TaskHandler::TaskHandler(QQmlApplicationEngine* engine, PGconn* conn, RegHandler* rh, QObject* parent) //? tmp
    : m_conn(conn), m_engine(engine), m_rh(rh), QObject(parent)
{
    m_tasks = new std::vector<Task*>;
    m_lvtask = new LVTask(this);
    m_lvtask->clear();
}

TaskHandler::~TaskHandler() {};

//? SETTING USER ON LOAD
void TaskHandler::setUser() { 
    m_user = m_rh->getUser();
    qDebug() << "USER DATA LOADED: " << m_user->getID();
    getAllUserTasks();
}

//? user data clear on close
void TaskHandler::clearUser() {
    m_user = nullptr;

    m_tasks->clear();
    m_lvtask->clear();
}

/* 
? WINDOW OPENERS
* adminWin.qml
* tasks.qml
* taskAdditon.qml */
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

void TaskHandler::openEditorWin(const int& t_qid) {
    if (!m_taskAddWin) {
        QQmlComponent component(m_engine, QUrl(QStringLiteral("qrc:/ui/taskEditor.qml")));
        QObject* m_object = component.create();
        m_taskEditorWin = qobject_cast<QQuickWindow*>(m_object);
    }
    if (m_taskEditorWin) {
        m_taskEditorWin->show(); 
    }

    m_id = t_qid;
}

void TaskHandler::openAdminWin() {
    if (!m_adminWin) {
        QQmlComponent component(m_engine, QUrl(QStringLiteral("qrc:/ui/adminPannel.qml")));
        QObject* m_object = component.create();
        m_adminWin = qobject_cast<QQuickWindow*>(m_object);
    }
    if (m_adminWin) {
        m_adminWin->show(); 
    }
}

void TaskHandler::openPhotoWin() {
    if (!m_photoWin) {
        QQmlComponent component(m_engine, QUrl(QStringLiteral("qrc:/ui/photoWin.qml")));
        QObject* m_object = component.create();
        m_photoWin = qobject_cast<QQuickWindow*>(m_object);
    }
    if (m_photoWin) {
        m_photoWin->show(); 
    }
}

void TaskHandler::closeAdditionWin() {
    m_taskAddWin->hide();
}

void TaskHandler::closeEditorWin() {
    m_taskEditorWin->hide();
}

void TaskHandler::closeAdminWin() {
    m_adminWin->hide();
}

void TaskHandler::closePhotoWin() {
    m_photoWin->hide();

}
//? END OF WINDOW OPENERS

//TODO: add inserting time done expired;
//? db adding/removing task
void TaskHandler::insertDBTask(std::string task_name, std::string task_text, std::string task_status) {
    std::string id = std::to_string(m_user->getID());

    std::string query = "INSERT INTO tasks(user_id, task_name, task_text, expire_time, is_expired, status) VALUES (" + id + ", '" + task_name + "', '" + task_text + "', '13:13:13', 't', '" + task_status + "')";
    
    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        qDebug() << "\n\tFAILED TO INSERT THE TASK: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return;
    }

    PQclear(res);
    qDebug() << "\tTASK INSERTED\n";
}

void TaskHandler::editDBTask(Task task, int task_id) {
    std::string id = std::to_string(m_user->getID());

    std::string query = "UPDATE tasks SET "
                    "user_id = " + id + ", "
                    "task_name = '" + *task.getTaskName() + "', "
                    "task_text = '" + *task.getTaskText() + "', "
                    "expire_time = '13:13:13', "
                    "is_expired = 't', "
                    "status = '" + *task.getStatus() + "' "
                    "WHERE id = " + std::to_string(task_id) + ";";
    
    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        qDebug() << "\n\tFAILED TO INSERT THE TASK: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return;
    }

    PQclear(res);
    qDebug() << "\tTASK INSERTED\n";
}

void TaskHandler::removeDBTask(int task_id) {
    std::string query = "DELETE FROM tasks WHERE task_id = " + std::to_string(task_id) + "";

    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        qDebug() << "\n\tFAILED TO DELETE THE TASK: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return;
    }

    PQclear(res);
    qDebug() << "\n\tTASK DELETED FROM DB";
}

//? qml adding/removing 
//TODO fix (if task plate outside of the view u'll get error:)
//! libc++abi: terminating due to uncaught exception of type std::out_of_range: vector
//! [1]    89411 abort      ./DayPlanner
void TaskHandler::delTask(const int& task_id) {
    qDebug() << "\tREG HANDLER: " << m_rh->getWin();
    m_tasksWin = m_rh->getWin();

    if (task_id == -1) {
        qDebug() << "\nNO TASK CHOOSEN";
        return;
    }

    if (task_id >= m_lvtask->rowCount() || task_id < 0 || task_id >= m_tasks->size()) {
        qDebug() << "\nNO TASK CHOOSEN (out of index)" << task_id << m_tasks->size();
        qDebug() << "\nTASK AT 0 POS: " << m_tasks->at(0)->getID();

        for (auto task : *m_tasks) {
            qDebug() << task->getID() << "\n";
            qDebug() << task->getTaskName() << "\n";
        }
        return;
    }

    //? DEBUG ?//
    qDebug() << "\tTASK INDEX: " << task_id << "\n"; 
    qDebug() << "\tTASK DB_INDEX: " << m_tasks->at(task_id)->getID();
    qDebug() << "\tROWS: " << m_lvtask->rowCount();

    removeDBTask(m_tasks->at(task_id)->getID());
    m_lvtask->removeTask(task_id);
    reloadTasks();
}

void TaskHandler::addTask(
    const QString& t_qname, 
    const QString& t_qstatus, 
    const QString& t_qtext
) {
    std::string* t_name = new std::string(t_qname.toStdString());
    std::string* t_text = new std::string(t_qtext.toStdString());
    std::string* t_status = new std::string(t_qstatus.toStdString());

    insertDBTask(*t_name, *t_text, *t_status);

    Task* task = new Task();
    task->setTaskName(t_name);
    task->setTaskText(t_text);
    task->setStatus(t_status);

    m_lvtask->addTask(task);
    qDebug() << "\n\tTASK ADDED FOR USER: " << m_user->getID();

    reloadTasks();
}

void TaskHandler::editTask(
    const QString& t_qname, 
    const QString& t_qstatus, 
    const QString& t_qtext
) {
    std::string* t_name = new std::string(t_qname.toStdString());
    std::string* t_text = new std::string(t_qtext.toStdString());
    std::string* t_status = new std::string(t_qstatus.toStdString());
    

    if (m_id == -1) {
        qDebug() << "\nNO TASK CHOOSEN";
        return;
    }

    if (m_id >= m_lvtask->rowCount() || m_id < 0 || m_id >= m_tasks->size()) {
        qDebug() << "\nNO TASK CHOOSEN (out of index)";
        return;
    }

    Task* task = new Task();
    task->setTaskName(t_name);
    task->setTaskText(t_text);
    task->setStatus(t_status);
    task->setPhoto(m_tasks->at(m_id)->hasPhoto());

    // DATABASE TASK CHANGE 
    editDBTask(
        *task,
        m_tasks->at(m_id)->getID()
    );

    // M_LVTASKS TASK REPLACMENT
    m_lvtask->editTask(task, m_id);
    reloadTasks();
}

void TaskHandler::getAllUserTasks() {
    std::string query = "SELECT * FROM tasks WHERE user_id = '" + std::to_string(m_user->getID()) + "';"; 

    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        qDebug() << "\nFAILED TO GET TASKS: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return;
    }

    if (PQntuples(res) == 0) {
        qDebug() << "No user tasks found\n\t USER: " << m_rh->getQUsername();
        PQclear(res);
        return;
    }
    
    int nRows = PQntuples(res);  
    if (m_tasks) {    
        for (int row = 0; row < nRows; row++) {
            Task* task = new Task(); 
        
            std::string* t_name = new std::string(PQgetvalue(res, row, 2));
            std::string* t_text = new std::string(PQgetvalue(res, row, 3));
            std::string* t_time = new std::string(PQgetvalue(res, row, 4));
            std::string* t_status = new std::string(PQgetvalue(res, row, 6));
        
            task->setID(std::stoi(PQgetvalue(res, row, 0)));
            task->setTaskName(t_name);
            task->setTaskText(t_text);
            task->setStatus(t_status);
            task->setTime(t_time);

            bool tmp = (std::string(PQgetvalue(res, row, 5)) == "t");
            task->setExpired(tmp);

            task->setPhoto(hasDBPhoto(task->getID()));
        
            m_tasks->push_back(task);  
            if(m_lvtask) {
                qDebug() << "M_LVTASK ADDED: " << task;
                m_lvtask->addTask(task);        
            }
        }
    }

    //? DEBUG ?//
    qDebug() << "\nTASKS:";
    for (Task* task : *m_tasks) {
        qDebug() << "\n\tTASK ID: "<< task->getID() 
        << "\n\tTASK NAME: " << QString::fromUtf8(task->getTaskName()->c_str())
        << "\n\tTASK TEXT: " << QString::fromUtf8(task->getTaskText()->c_str())
        << "\n\tTASK TIME" << QString::fromUtf8(task->getTime()->c_str())
        << "\n\tTASK STATUS: " << QString::fromUtf8(task->getStatus()->c_str())
        << "\n\tTASK EPIRED: " << task->getExpire()
        << "\n\tHAS PHOTO: " <<  task->hasPhoto() << "\n";
    }

    PQclear(res);
}

void TaskHandler::sortByTaksStatus() {
    m_lvtask->sortByStatus();
}

void TaskHandler::deleteDBUser(const int& user_id) {
    std::string query = "DELETE FROM users WHERE id = '" + std::to_string(user_id) + "';";
    
    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        qDebug() << "\n\tFAILED TO DELETE USER: " << PQerrorMessage(m_conn) << "\n";
        PQclear(res);
        return;
    }

    PQclear(res);
    qDebug() << "\tUSER DELETED\n";
}

std::vector<char> TaskHandler::readFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);

    if (!file) {
        throw std::runtime_error("Cannot open file: " + path);
    }

    return std::vector<char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void TaskHandler::addPhoto(const QString& fpath, const int& tid) {
    if (tid < 0 || tid >= m_tasks->size()) {
        qDebug() << "TASK ID ERROR";
        return;
    }

    if(tid < 0) {
        qDebug() << "TASK NOT SELECTED";
        return;
    }
    qDebug() << "CHOOSEN TASK ID: " << tid;
    qDebug() << "CHOOSEN TASK ID IN DB: " << m_tasks->at(tid)->getID();

    QString localPath = QUrl(fpath).toLocalFile();
    std::string filePath = localPath.toStdString();

    std::vector<char> fileData = readFile(filePath);

    const char* paramValues[2];
    int paramLengths[2];
    int paramFormats[2] = {1, 0}; 

    paramValues[0] = fileData.data();
    paramLengths[0] = static_cast<int>(fileData.size());

    std::string taskIdStr = std::to_string(m_tasks->at(tid)->getID());
    paramValues[1] = taskIdStr.c_str();
    paramLengths[1] = static_cast<int>(taskIdStr.length());

    const char* query = "UPDATE tasks SET file = $1 WHERE task_id = $2";

    PGresult* res = PQexecParams(
        m_conn,
        query,
        2,
        nullptr,
        paramValues,
        paramLengths,
        paramFormats,
        0
    );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        qDebug() << "FAILED TO UPLOAD PHOTO: " << PQerrorMessage(m_conn);
        PQclear(res);
        return;
    }

    PQclear(res);
    qDebug() << "PHOTO SUCCESSFULY UPLOADED";

    reloadTasks();
}

QByteArray TaskHandler::getPhotoFile(int task_id) {
    QByteArray result;
    std::string query = "SELECT file FROM tasks WHERE task_id = '" + std::to_string(m_tasks->at(task_id)->getID()) + "';";

    PGresult* res = PQexec(m_conn, query.c_str());
    if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0) {
        size_t unescapedLength;
        unsigned char* unescapedData = PQunescapeBytea(
            reinterpret_cast<const unsigned char*>(PQgetvalue(res, 0, 0)),
            &unescapedLength
        );

        result = QByteArray(reinterpret_cast<const char*>(unescapedData), unescapedLength);

        PQfreemem(unescapedData);
    }
    PQclear(res);
    return result;
}

void TaskHandler::writeFileData(const int& task_id) {
    QByteArray imageData = getPhotoFile(task_id);
    qDebug() << "IMAGE DATA SIZE:" << imageData.size();

    if(imageData.size() == 0) {
        qDebug() << "NO PHOTO TO BE LOADED";
        return;
    }

    QFile file("../tmp/tmp_image.jpg");
    file.open(QIODevice::WriteOnly);
    file.write(imageData);
    file.close();
}

QString TaskHandler::getFilePath() {
    QString filePath = QDir::currentPath() + "/../tmp/tmp_image.jpg";
    QString fileUrl = QUrl::fromLocalFile(filePath).toString();

    return fileUrl;
}

bool TaskHandler::hasDBPhoto(int id) {
    std::string query = "SELECT (file IS NOT NULL AND length(file) > 0) AS file_bool FROM tasks WHERE task_id = " + std::to_string(id) + "";
    PGresult* res = PQexec(m_conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        qDebug() << "FAILED: " << PQerrorMessage(m_conn);
        PQclear(res);
        return false;
    }

    int rows = PQntuples(res);
    std::string result = PQgetvalue(res, 0, 0);
    bool hasPhoto = result == "t" ? true : false;
    qDebug() << "=========HAS_PHOTO========>" << hasPhoto << "<========ID========>" << id;

    PQclear(res);
    return hasPhoto;
}

void TaskHandler::reloadTasks() {
    m_tasks->clear();
    m_lvtask->clear();
    getAllUserTasks();
}