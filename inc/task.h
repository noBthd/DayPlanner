#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
    public: 
        Task(
            std::string* name = nullptr, 
            std::string* text = nullptr
        );
        ~Task();

        // addTask func
        std::string getTaskName();
        std::string getTaskText();
        bool getDone();
        bool getExpire();
        
        bool setTaskName(std::string);
        bool setTaskText(std::string);
        void done();
        void expired();
    private:
        int m_id;
        // time
        std::string m_task_name;
        std::string m_task_text;

        // done/not 
        bool m_done = false; 
        // expired/not
        bool m_expidred = false;
};

#endif