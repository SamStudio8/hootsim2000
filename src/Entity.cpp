#include <sstream>
#include <string>

#include "Entity.h"
#include "MessageQueue.h"

Entity::Entity(){

}

Entity::~Entity(){
    //TODO(samstudio8)
}

Entity::Entity(MessageQueue* mq){
    this->mq = mq;
}

int Entity::get_id(){
    return this->id;
}
void Entity::set_id(int id){
    this->id = id;
}


void Entity::add_property(std::string key, float value){

    this->properties.insert(std::pair<std::string, float>(key, value));
    
    std::ostringstream oss;
    oss << "Entity E" << this->get_id() << " adds property pair " << key << ":" << value;
    std::string msg = oss.str();
    this->mq->broadcast(std::string("add_property"), -1, this->get_id(), msg);
}

std::map< std::string, float > Entity::get_properties()
{
    return this->properties;
}

