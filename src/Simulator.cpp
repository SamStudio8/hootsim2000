#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Controller.h"
#include "Entity.h"
#include "MessageQueue.h"
#include "Simulator.h"

Simulator::Simulator(){
    this->id_autoincrement = 1;
}

Simulator::Simulator(MessageQueue* mq){
    this->mq = mq;
    this->mq->subscribe(std::string("add_prop"), this);
    this->id_autoincrement = 1;
}

Simulator::~Simulator(){
    //TODO(samstudio8)
}

void Simulator::register_controller(Controller* c){
    c->set_id(this->id_autoincrement++);
    this->registered_controllers.insert(std::pair<int, Controller*>(c->get_id(), c));
}

void Simulator::register_entity(Entity* e){
    e->set_id(this->id_autoincrement++);
    this->registered_entities.insert(std::pair<int, Entity*>(e->get_id(), e));
}


void Simulator::super_notify(const std::string& msg_type, int to, int from, const std::string& message){
    (void)message;
    (void)to;
        
    if (msg_type.compare(std::string("add_prop")) == 0){
        this->auto_attach_controllers(from);
    }
}

void Simulator::auto_attach_controllers(int eid){
    //TODO Catch invalid entity
    Entity* e = this->registered_entities.find(eid)->second;
    
    for(std::map<int, Controller*>::iterator it=this->registered_controllers.begin(); it!=this->registered_controllers.end(); ++it){
        // If entity matches requirements for the current controller, attach it
        if( it->second->meets_requirements(e) ){
            it->second->attach_entity(e);
            
            std::ostringstream oss;
            oss << "Simulator auto attached E" << e->get_id() << " to C" << it->second->get_id() << " after meeting requirements";
            std::string msg = oss.str();
            this->mq->broadcast(std::string("auto_attach"), -1, 0, msg);
        }
        
    }    
}

void Simulator::tick(){
    this->mq->broadcast(std::string("sim_tick"), -1, 0, std::string("Simulation tick."));
}

MessageQueue* Simulator::get_messagequeue()
{
    return this->mq;
}


