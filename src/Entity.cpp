#include "Entity.h"

Entity::Entity(){

}

Entity::~Entity(){

}

Entity::Entity(MessageQueue*){

}

void Entity::add_property(std::string key, float value){
    this->properties.insert(std::pair<std::string, float>(key, value));
}

std::map< std::string, float > Entity::get_properties()
{
    return this->properties;
}

