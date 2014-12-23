#ifndef REGISTERABLE_H
#define REGISTERABLE_H

class Registerable {
public:
    virtual ~Registerable() {}
    
    void set_messagequeue(class MessageQueue* mq){
        this->mq = mq;
    }
    
    void set_id(int id){
        this->id = id;
    }
    int get_id(){
        return this->id;
    }
    
protected:
    int id;
    class MessageQueue* mq;
};

#endif // REGISTERABLE_H