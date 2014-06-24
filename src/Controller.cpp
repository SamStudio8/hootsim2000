#include <iostream>
#include <map>

#include "Controller.h"
#include "Entity.h"

Controller::Controller(){

}

Controller::Controller(MessageQueue* mq){
    this->mq = mq;
}

Controller::~Controller(){

}

void Controller::add_requirement(std::string requirement){
    this->requirements.insert(requirement);
}

std::set< std::string > Controller::get_requirements(){
    return this->requirements;
}

bool Controller::meets_requirements(Entity* e){
    std::map<std::string, float> properties = e->get_properties();
    for(size_t pIndex=0; pIndex < properties.size(); pIndex++){
    }
    return false;
}



