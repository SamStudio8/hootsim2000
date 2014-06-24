#include <iostream>

#include "Simulator.h"
#include "MessageQueue.h"
#include "Controller.h"

class HootController: public Controller {
    using Controller::Controller;
};

int main(){
    Simulator s;
    MessageQueue mq;
    
    HootController hc(&mq);
    hc.add_requirement("hooting");
    hc.add_requirement("nocturnal");
    
    std::cout << "HootController Requirements:";
    for (std::set<std::string>::iterator it=hc.get_requirements().begin(); it!=hc.get_requirements().end(); ++it){
        std::cout << ' ' << *it << ',';
    }
    std::cout << '\n';
    
    return 0;
}