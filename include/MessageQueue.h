#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

class MessageQueue {
public:
    MessageQueue();
    ~MessageQueue();
    
    void subscribe();
    void broadcast();
};

#endif // MESSAGEQUEUE_H
