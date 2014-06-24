#include <iostream>
#include <map>

#include "Controller.h"
#include "Entity.h"
#include "MessageQueue.h"

MessageQueue::MessageQueue(){

}

MessageQueue::~MessageQueue(){
    //TODO(samstudio8)
}

void MessageQueue::broadcast(std::string msg_type){
    //this->broadcast(msg_type, nullptr);
    std::cout << "[_MQ_] Broadcasting "<< msg_type << "\n";
    
    // Notify Subscribers
    if (this->subscribers.find(msg_type) != this->subscribers.end()){
        std::vector<Controller*> subscribers = this->subscribers.at(msg_type);
        for (size_t index=0; index < subscribers.size(); index++){
            subscribers.at(index)->notify(msg_type);
        }
    }
    
}

void MessageQueue::broadcast(std::string msg_type, Entity* e){
    
    this->broadcast(msg_type);
    for (std::map<std::string, float>::iterator it=e->get_properties().begin(); it!=e->get_properties().end(); ++it){}
}

void MessageQueue::subscribe(std::string msg_type, Controller* subscriber){
    //TODO(samstudio8) This just happens to work, look away now.
    std::vector<Controller*> subscribers;
    subscribers.push_back(subscriber);
    this->subscribers.insert(std::pair<std::string, std::vector<Controller*>>(msg_type, subscribers));
}

