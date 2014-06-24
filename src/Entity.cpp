#include "Entity.h"

Entity::Entity(){

}

Entity::~Entity(){

}

std::map< std::string, float > Entity::get_properties()
{
    return this->properties;
}

