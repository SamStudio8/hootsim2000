#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Controller.h"
#include "Entity.h"
#include "Simulator.h"
#include "MessageQueue.h"

Controller::Controller(Simulator* sim){
    this->set_messagequeue(sim->get_messagequeue());
    sim->register_controller(this);
}

void Controller::set_id(int id){
    this->id = id;
}

Entity* Controller::get_entity(int eid){
    //TODO Catch invalid entity
    return this->entities.find(eid)->second;
}

void Controller::add_requirement(const std::string& requirement){
    
    this->requirements.insert(requirement);
    
    std::ostringstream oss;
    oss << "Controller C" << this->get_id() << " adds " << requirement << " as requirement";
    std::string msg = oss.str();
    this->mq->broadcast(std::string("add_require"), -1, this->get_id(), msg);
}

std::set< std::string > Controller::get_requirements(){
    return this->requirements;
}

bool Controller::meets_requirements(Entity* e){
    std::map<std::string, float> properties = e->get_properties();
    
    for (std::set<std::string>::iterator it=this->requirements.begin(); it!=this->requirements.end(); ++it){
        if(properties.find(*it) == properties.end()){
            return false;
        }
    }
    return true;
}

void Controller::attach_entity(Entity* e){
    this->entities.insert(std::pair<int, Entity*>(e->get_id(), e));
}

void Controller::super_notify(const std::string& msg_type, int to, int from, const std::string& message){
    //NOTE The SimController does not contain any entities (as its pointer to Simulator is not Entity)
    //     this causes messages sent to -1 rather than 0 to not reach the required controller...
    if (to >= 0){
        this->notify(msg_type, to, from, message);
    }
    else{        
        for(std::map<int, Entity*>::iterator it=this->entities.begin(); it!=this->entities.end(); ++it){
            this->notify(msg_type, it->first, from, message);
        }
    }
}
