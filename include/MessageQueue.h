#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <map>
#include <string>
#include <vector>

class MessageQueue {
public:
    MessageQueue();
    ~MessageQueue();
    
    void subscribe(const std::string& msg_type, class Receiver* subscriber);
    void broadcast(const std::string& msg_type, int to, int from, const std::string& message);
    
private:
    std::map<std::string, std::vector<class Receiver*>> subscribers;
};

#endif // MESSAGEQUEUE_H
