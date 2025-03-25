#ifndef TASK_H
#define TASK_H

#include <string>
#include <QDebug>
#include "libpq-fe.h"
#include "sql/pgconn.h"

class Task {
    public: 
        Task(
            PGconn* conn = nullptr,
            std::string* name = nullptr, 
            std::string* text = nullptr
        );

        ~Task();

        std::string getTaskName();
        std::string getTaskText();
        bool getDone();
        bool getExpire();
        
        void setTaskName(std::string);
        void setTaskText(std::string);
        void done();
        void expired();

        
        private:
        PGconn* m_conn;
        
        // time
        int m_id;
        std::string* m_task_name;
        std::string* m_task_text;
        
        // done/not 
        bool m_done = false; 
        // expired/not
        bool m_expidred = false;
        
        void setNewId();
        int getPrevId();

};

#endif