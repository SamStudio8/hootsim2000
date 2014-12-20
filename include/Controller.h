#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <set>
#include <string>

class Controller {
public:
    Controller();
    Controller(class MessageQueue* mq);
    ~Controller();
    
    void add_requirement(const std::string& requirement);
    std::set<std::string> get_requirements();
    bool meets_requirements(class Entity* e);
    virtual void notify(const std::string& msg_type, int to, int from, const std::string& message) = 0;
    void cnotify(const std::string& msg_type, int to, int from, const std::string& message);
    void set_id(int);
    int get_id();
    void attach_entity(class Entity*);
    class Entity* get_entity(int eid);
    
protected:
    class MessageQueue* mq;
    std::map<int, class Entity*> entities;
private:
    int id;
    std::set<std::string> requirements;
};

#endif // CONTROLLER_H
