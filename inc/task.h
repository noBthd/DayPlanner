#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
    public: 
        Task();
        ~Task();

        // addTask func
        std::string getTaskName();
        std::string getTaskText();
        
    private:
        // time
        // done/not
        std::string m_task_name;
        std::string m_task_text;
};

#endif