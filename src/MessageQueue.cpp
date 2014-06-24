#include <iostream>
#include <map>

#include "Controller.h"
#include "Entity.h"
#include "MessageQueue.h"

MessageQueue::MessageQueue(){

}

MessageQueue::~MessageQueue(){

}

void MessageQueue::broadcast(std::string msg_type, Entity* e){
    
    // Notify Subscribers
    std::vector<Controller*> subscribers = this->subscribers.at(msg_type);
    for (size_t index=0; index < subscribers.size(); index++){
        subscribers.at(index)->notify(msg_type);
    }
    
    // Log to Console
    std::cout << msg_type;
    std::cout << "\nProperties:\n";
    for (std::map<std::string, float>::iterator it=e->get_properties().begin(); it!=e->get_properties().end(); ++it){
        std::cout << it->first << " => " << it->second << '\n';
    }
    std::cout << '\n';
}

void MessageQueue::subscribe(std::string msg_type, Controller* subscriber){
    std::vector<Controller*> subscribers;
    subscribers.push_back(subscriber);
    this->subscribers.insert(std::pair<std::string, std::vector<Controller*>>(msg_type, subscribers));
}

