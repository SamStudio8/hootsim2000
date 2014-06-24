#include "Simulator.h"
#include <MessageQueue.h>

Simulator::Simulator(){

}

Simulator::Simulator(MessageQueue* mq){
    this->mq = mq;
}

Simulator::~Simulator(){

}
