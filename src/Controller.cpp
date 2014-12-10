#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Controller.h"
#include "Entity.h"
#include "MessageQueue.h"

Controller::Controller(){

}

Controller::Controller(MessageQueue* mq){
    this->mq = mq;
}

Controller::~Controller(){
    //TODO(samstudio8)
}

void Controller::set_id(int id){
    this->id = id;
}

int Controller::get_id(){
    return this->id;
}

Entity* Controller::get_entity(){
    return this->entity;
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
    this->entity = e;
}
