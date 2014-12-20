#include <iostream>
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

float Entity::get_property(const std::string& key){
    if(this->properties.find(key) != this->properties.end()){
        return this->properties.at(key);
    }
    else{
        std::cout << "Tried to get value for " << key;
        return 0;
    }
}

void Entity::update_property(const std::string& key, float value){
    if(this->properties.find(key) != this->properties.end()){
        this->properties.at(key) = value;
        
        std::ostringstream oss;
        oss << "Entity E" << this->get_id() << " updates property pair " << key << ":" << value;
        std::string msg = oss.str();
        this->mq->broadcast(std::string("update_prop"), 0, this->get_id(), msg);
    }
    else{
        // Naughty
    }
}

void Entity::add_property(const std::string& key, float value){

    this->properties.insert(std::pair<std::string, float>(key, value));
    
    std::ostringstream oss;
    oss << "Entity E" << this->get_id() << " adds property pair " << key << ":" << value;
    std::string msg = oss.str();
    this->mq->broadcast(std::string("add_prop"), 0, this->get_id(), msg);
}

std::map< std::string, float > Entity::get_properties()
{
    return this->properties;
}

