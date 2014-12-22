#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <map>
#include <string>
#include <vector>

#include "Receiver.h"

class Simulator: public Receiver {
public:
    Simulator();
    Simulator(class MessageQueue*);
    ~Simulator();
    
    void register_controller(class Controller*);
    void register_entity(class Entity*);
    void tick();
    
    void super_notify(const std::string& msg_type, int to, int from, const std::string& message);
    
    class MessageQueue* get_messagequeue();
private:
    void auto_attach_controllers(int eid);
    
    int id_autoincrement;
    
    std::map<int, class Entity*> registered_entities;
    std::map<int, class Controller*> registered_controllers;
    
};

#endif // SIMULATOR_H
