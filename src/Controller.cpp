#include <iostream>
#include <map>

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

void Controller::add_requirement(std::string requirement){
    this->requirements.insert(requirement);
    this->mq->broadcast(std::string("add_requirement"));
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



