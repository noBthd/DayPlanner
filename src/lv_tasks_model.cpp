#include "lv_tasks_model.h"
// #include <cstddef>

LVTask::LVTask(QObject* parent)
    : QAbstractListModel(parent)
{
    Task* task123 = new Task();
    std::string test = "test";   
    task123->setTaskName(&test); 
    task123->setTaskText(&test); 
    task123->setStatus(&test); 

    m_tasks.append(task123);
}

int LVTask::rowCount(const QModelIndex& parent) const {
    if (parent.isValid())
        return 0;
    return m_tasks.size();
}

QVariant LVTask::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_tasks.size())
        return {};

    Task* task = m_tasks.at(index.row());

    switch (role) {
        case IdRole: return task->getID();
        case NameRole: return QString::fromStdString(*task->getTaskName());
        case TextRole: return QString::fromStdString(*task->getTaskText());
        case StatusRole: return QString::fromStdString(*task->getStatus());
        default: return {};
    }
}

QHash<int, QByteArray> LVTask::roleNames() const {
    return {
        { IdRole, "id" },
        { NameRole, "name" },
        { TextRole, "text" },
        { StatusRole, "status"}
    };
}

void LVTask::addTask(Task* task) {
    beginInsertRows(QModelIndex(), m_tasks.size(), m_tasks.size());
    m_tasks.append(task);
    endInsertRows();
}

void LVTask::removeTask(int task_id) {
    beginRemoveRows(QModelIndex(), task_id, task_id);
    delete m_tasks.takeAt(task_id); 
    endRemoveRows();

    qDebug() << "\n\tTASK REMOVED FROM QLIST: " << task_id;
}

void LVTask::clear() {
    beginResetModel();
    m_tasks.clear();
    endResetModel();
}

void LVTask::sortByStatus() {
    beginResetModel();
    std::sort(m_tasks.begin(), m_tasks.end(), [](Task* a, Task* b) {
        auto getStatusPriority = [](const std::string& status) {
            if (status == "done") return 0;
            if (status == "in progress") return 1;
            if (status == "not done") return 2;
            return 3; // если вдруг какой-то другой статус
        };

        return getStatusPriority(*(a->getStatus())) < getStatusPriority(*(b->getStatus()));
    });
    endResetModel();
}