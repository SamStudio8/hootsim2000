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

void Entity::add_property(std::string key, float value){
    this->properties.insert(std::pair<std::string, float>(key, value));
    this->mq->broadcast(std::string("add_property"), this);
}

std::map< std::string, float > Entity::get_properties()
{
    return this->properties;
}

