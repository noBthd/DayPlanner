#ifndef LV_TASKS_MODEL
#define LV_TASKS_MODEL

#include <QAbstractListModel>
#include <QList>
#include "task.h"

class LVTask : public QAbstractListModel {
    Q_OBJECT;

    public:
        enum Roles {
            IdRole = Qt::UserRole + 1,
            NameRole,
            TextRole, 
            StatusRole,
            photoRole
        };

        explicit LVTask(QObject* parent = nullptr); 

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;
        QHash<int, QByteArray> roleNames() const override;
    
        void addTask(Task*);
        void removeTask(int);
        void editTask(Task*, int);
        void clear();
        
        void sortByStatus();

    private:
        QList<Task*> m_tasks;
};

#endif