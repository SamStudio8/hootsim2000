#include <iostream>
#include <map>

#include "Controller.h"
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


void Simulator::notify(std::string message){
    if (message.compare(std::string("add_property")) == 0){
        // Currently nukes all controllers.
        // In future, messages will specify the originating entity.
        std::cout << "[SIM_] Received instruction to destroy all controllers after add_property" << "\n"; 
        this->controllers.clear();
        this->auto_attach_controllers();
    }
    if (message.compare(std::string("auto_attach")) == 0){
        std::cout << "[SIM_] Received confirmation of auto_attach" << "\n";         
    }
}

void Simulator::auto_attach_controllers(){
    // Currently called for all entities and all controllers, which is most bad.
    for (size_t eIndex=0; eIndex < this->registered_entities.size(); eIndex++){
        for (size_t cIndex=0; cIndex < this->registered_controllers.size(); cIndex++){

            if( this->registered_controllers.at(cIndex)->meets_requirements(this->registered_entities.at(eIndex)) ){
                this->controllers.insert(std::pair<Entity*, Controller*>(
                    this->registered_entities.at(eIndex),
                    this->registered_controllers.at(cIndex)
                ));
                this->mq->broadcast(std::string("auto_attach"));
            }
        }        
    }
}


