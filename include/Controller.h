#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <set>
#include <string>

#include "Receiver.h"

class Controller: public Receiver {
public:
    Controller();
    Controller(class Simulator* sim);
    
    virtual ~Controller() {}
    
    void add_requirement(const std::string& requirement);
    std::set<std::string> get_requirements();
    bool meets_requirements(class Entity* e);
    void set_id(int);
    void attach_entity(class Entity*);
    class Entity* get_entity(int eid);

    void super_notify(const std::string& msg_type, int to, int from, const std::string& message);    
    virtual void notify(const std::string& msg_type, int to, int from, const std::string& message) = 0;
    
protected:
    std::map<int, class Entity*> entities;
private:
    std::set<std::string> requirements;
};

#endif // CONTROLLER_H
