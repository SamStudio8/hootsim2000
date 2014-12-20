#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <map>
#include <string>
#include <vector>

class Simulator {
public:
    Simulator();
    Simulator(class MessageQueue*);
    ~Simulator();
    
    void notify(const std::string& msg_type, int to, int from, const std::string& message);
    void register_controller(class Controller*);
    void register_entity(class Entity*);
    void tick();
private:
    class MessageQueue* mq;
    std::vector<class Entity*> registered_entities;
    std::vector<class Controller*> registered_controllers;
    std::map<class Entity*, class Controller*> controllers;
    void auto_attach_controllers();
};

#endif // SIMULATOR_H
