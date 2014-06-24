#include <iostream>
#include <map>

#include "Controller.h"
#include "Entity.h"
#include "MessageQueue.h"

MessageQueue::MessageQueue(){
    std::cout << "TO" << "\t" << "FROM" << "\t" << "MESSAGE" << "\n";
}

MessageQueue::~MessageQueue(){
    //TODO(samstudio8)
}

void MessageQueue::broadcast(std::string msg_type, int to, int from, std::string message){
    
    std::cout << to << "\t" << from << "\t" << message << "\n";
    // Notify Subscribers (if there are any)
    if (this->subscribers.find(msg_type) != this->subscribers.end()){
        std::vector<Controller*> subscribers = this->subscribers.at(msg_type);
        for (size_t index=0; index < subscribers.size(); index++){
            if(to > 0){
                if(subscribers.at(index)->get_id() == to){
                    subscribers.at(index)->notify(msg_type);
                    break;
                }
            }
            else{
                subscribers.at(index)->notify(msg_type);
            }
        }
    }
}

void MessageQueue::subscribe(std::string msg_type, Controller* subscriber){
    //TODO(samstudio8) This just happens to work, look away now.
    std::vector<Controller*> subscribers;
    subscribers.push_back(subscriber);
    this->subscribers.insert(std::pair<std::string, std::vector<Controller*>>(msg_type, subscribers));
}

