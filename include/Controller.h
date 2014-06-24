#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <set>

class Controller {
public:
    Controller();
    explicit Controller(class MessageQueue*);
    ~Controller();
    
    void add_requirement(std::string);
    std::set<std::string> get_requirements();
    bool meets_requirements(class Entity* e);
private:
    class MessageQueue* mq;
    std::set<std::string> requirements;
};

#endif // CONTROLLER_H
