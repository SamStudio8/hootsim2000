#include <iostream>

#include "Controller.h"
#include "Entity.h"
#include "MessageQueue.h"
#include "Simulator.h"

class HootController: public Controller {
    using Controller::Controller;
};

int main(){
    Simulator s;
    MessageQueue mq;
    
    HootController hc(&mq);
    hc.add_requirement("hooting");
    hc.add_requirement("nocturnal");
    
    std::cout << "HootController Requirements:\n";
    for (std::set<std::string>::iterator it=hc.get_requirements().begin(); it!=hc.get_requirements().end(); ++it){
        std::cout << *it << '\n';
    }
    std::cout << '\n';
    
    Entity hoot(&mq);
    hoot.add_property("nocturnal", 1);
    hoot.add_property("hoot", 1);
    hoot.add_property("health", 100);
    
    std::cout << "\nHoot Properties:\n";
    for (std::map<std::string, float>::iterator it=hoot.get_properties().begin(); it!=hoot.get_properties().end(); ++it){
        std::cout << it->first << " => " << it->second << '\n';
    }
    std::cout << '\n';
    return 0;
}