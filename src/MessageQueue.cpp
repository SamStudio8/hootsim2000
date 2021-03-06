#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Receiver.h"
#include "Entity.h"
#include "MessageQueue.h"

MessageQueue::MessageQueue(){
    std::cout << "TO" << "\tFROM" << "\tMSG_TYPE" << "\tMESSAGE" << "\n";
}

MessageQueue::~MessageQueue(){
    //TODO(samstudio8)
}

void MessageQueue::broadcast(const std::string& msg_type, int to, int from, const std::string& message){
    
    std::cout << to << "\t" << from << "\t" << msg_type << "\t" << message << "\n";
    // Notify Subscribers (if there are any)
    if (this->subscribers.find(msg_type) != this->subscribers.end()){
        std::vector<Receiver*> subscribers = this->subscribers.at(msg_type);
        for (size_t index=0; index < subscribers.size(); index++){
                subscribers.at(index)->super_notify(msg_type, to, from, message);                
        }
    }
}

void MessageQueue::subscribe(const std::string& msg_type, Receiver* subscriber){

    // If this is the first subscription of its kind, add it, otherwise append to the right vector
    if(this->subscribers.find(msg_type) != this->subscribers.end()){
        this->subscribers.find(msg_type)->second.push_back(subscriber);
    }
    else{
        std::vector<Receiver*> subscribers;
        subscribers.push_back(subscriber);
        this->subscribers.insert(std::pair<std::string, std::vector<Receiver*>>(msg_type, subscribers));
    }
    
    std::ostringstream oss;
    oss << "Receiver C" << subscriber->get_id() << " listening for " << msg_type;
    std::string msg = oss.str();
    this->broadcast(std::string("subscription"), -1, -1, msg);
}

