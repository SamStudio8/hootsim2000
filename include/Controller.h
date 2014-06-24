#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <set>

class Controller {
public:
    Controller();
    Controller(class MessageQueue* mq);
    ~Controller();
    
    void add_requirement(std::string);
    std::set<std::string> get_requirements();
    bool meets_requirements(class Entity* e);
    virtual void notify(std::string) = 0;
    void set_id(int);
    int get_id();
    virtual void tick() = 0;
    void attach_entity(class Entity*);
    class Entity* get_entity();
    
protected:
    class MessageQueue* mq;
    class Entity* entity;
private:
    int id;
    std::set<std::string> requirements;
};

#endif // CONTROLLER_H
