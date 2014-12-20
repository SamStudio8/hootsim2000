#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Controller.h"
#include "Entity.h"
#include "MessageQueue.h"
#include "Simulator.h"

Simulator::Simulator(){

}

Simulator::Simulator(MessageQueue* mq){
    this->mq = mq;
}

Simulator::~Simulator(){
    //TODO(samstudio8)
}

void Simulator::register_controller(Controller* c){
    this->registered_controllers.push_back(c);
}

void Simulator::register_entity(Entity* e){
    this->registered_entities.push_back(e);
}


void Simulator::notify(const std::string& msg_type, int to, int from, const std::string& message){
    (void)message;
    (void)from;
    (void)to;
        
    if (msg_type.compare(std::string("add_prop")) == 0){
        // Currently nukes all controllers.
        // In future, messages will specify the originating entity.
        this->mq->broadcast(std::string("sim_dcon"), -1, 0, std::string("Simulator received instruction to destroy all controllers after add_property"));
        this->auto_attach_controllers();
    }
}

void Simulator::auto_attach_controllers(){
    // Currently called for all entities and all controllers, which is most bad.
    for (size_t eIndex=0; eIndex < this->registered_entities.size(); eIndex++){
        for (size_t cIndex=0; cIndex < this->registered_controllers.size(); cIndex++){
            if( this->registered_controllers.at(cIndex)->meets_requirements(this->registered_entities.at(eIndex)) ){
                this->registered_controllers.at(cIndex)->attach_entity(this->registered_entities.at(eIndex));
                
                std::ostringstream oss;
                oss << "Simulator auto attached E" << this->registered_entities.at(eIndex)->get_id() << " to C" << this->registered_controllers.at(cIndex)->get_id() << " after meeting requirements";
                std::string msg = oss.str();
                this->mq->broadcast(std::string("auto_attach"), -1, 0, msg);
            }
        }        
    }
}

void Simulator::tick(){
    this->mq->broadcast(std::string("sim_tick"), -1, 0, std::string("Simulation tick."));
}



