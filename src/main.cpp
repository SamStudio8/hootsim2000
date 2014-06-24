#include <iostream>

#include "Controller.h"
#include "Entity.h"
#include "MessageQueue.h"
#include "Simulator.h"

class SimController: public Controller {
public:
    SimController(Simulator* sim, MessageQueue* mq)
    : Controller(mq)
    {
        this->sim = sim;
        this->mq->subscribe(std::string("auto_attach"), this);
        this->mq->subscribe(std::string("add_property"), this);
    }
    
    void notify(std::string message){
        // Forward all messages to the simulator directly.
        this->sim->notify(message);
    }
private:
    Simulator* sim;
};

class HootController: public Controller {
public:
    HootController(MessageQueue* mq)
    : Controller(mq)
    {
        //this->mq->subscribe(std::string("hoot"), this);
    }
    
    void notify(std::string message){
        std::cout << message;
    }
};

int main(){

    MessageQueue mq;
    Simulator sim(&mq);
    
    SimController sc(&sim, &mq);
    
    HootController hc(&mq);
    sim.register_controller(&hc);
    hc.set_id(1);
    hc.add_requirement("hooting");
    hc.add_requirement("nocturnal");
    
    
    //std::cout << "HootController Requirements:\n";
    for (std::set<std::string>::iterator it=hc.get_requirements().begin(); it!=hc.get_requirements().end(); ++it){
        //std::cout << *it << '\n';
    }
    
    Entity hoot(&mq);
    sim.register_entity(&hoot);
    hoot.set_id(2);
    hoot.add_property("nocturnal", 1);
    hoot.add_property("hooting", 1);
    hoot.add_property("health", 100);
    
    //std::cout << "\nHoot Properties:\n";
    for (std::map<std::string, float>::iterator it=hoot.get_properties().begin(); it!=hoot.get_properties().end(); ++it){
        //std::cout << it->first << " => " << it->second << '\n';
    }
    return 0;
}