#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <map>
#include <string>
#include <vector>

class MessageQueue {
public:
    MessageQueue();
    ~MessageQueue();
    
    void subscribe(std::string msg_type, class Controller* subscriber);
    void broadcast(std::string, class Entity*);
    
private:
    std::map<std::string, std::vector<class Controller*>> subscribers;
};

#endif // MESSAGEQUEUE_H
