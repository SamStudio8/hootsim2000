#ifndef RECEIVER_H
#define RECEIVER_H

#include <string>

class Receiver {
public:
    virtual ~Receiver() {}
    
    virtual void super_notify(const std::string& msg_type, int to, int from, const std::string& message) = 0;

    void set_messagequeue(class MessageQueue* mq){
        this->mq = mq;
    }
    int get_id(){
        return this->id;
    }
    
protected:
    int id;
    class MessageQueue* mq;
};

#endif // RECEIVER_H
