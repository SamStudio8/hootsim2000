#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <set>

class Controller {
public:
    Controller();
    Controller(class MessageQueue*);
    ~Controller();
    
    void add_requirement(std::string);
    std::set<std::string> get_requirements();
    bool meets_requirements(class Entity* e);
    virtual void notify(std::string) = 0;
    
protected:
    class MessageQueue* mq;
private:
    std::set<std::string> requirements;
};

#endif // CONTROLLER_H
