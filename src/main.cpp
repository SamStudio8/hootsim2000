#include <iostream>
#include <sstream>
#include <string>

#include <unistd.h>

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
        this->set_id(0);
        this->mq->subscribe(std::string("add_prop"), this);
    }
    
    void notify(std::string message){
        // Forward all messages to the simulator directly.
        this->sim->notify(message);
    }
    
    void tick(){}
    
private:
    Simulator* sim;
};

class HootController: public Controller {
public:
    HootController(MessageQueue* mq)
    : Controller(mq)
    {
        this->mq->subscribe(std::string("health_pack"), this);
    }
    
    void notify(std::string message){
        if (message.compare(std::string("health_pack")) == 0){
            std::ostringstream oss;
            oss << "Entity E" << this->entity->get_id() << " health restored!";
            std::string msg = oss.str();
            this->mq->broadcast(std::string("health_okay"), -1, this->entity->get_id(), msg);
            this->entity->update_property("health", 100);
        }
    }
    
    void tick(){
        
        float ATTRITION_DAMAGE_PER_UNIT = 10;
        
        std::ostringstream oss;
        oss << "Entity E" << this->entity->get_id() << " suffers attrition!";
        std::string msg = oss.str();
        this->mq->broadcast(std::string("health_loss"), -1, this->entity->get_id(), msg);
        
        float health = this->entity->get_property("health");
        health = health - ATTRITION_DAMAGE_PER_UNIT;        
        this->entity->update_property("health", health);
        
        if (health <= 10){
            this->mq->broadcast(std::string("health_crit"), -1, this->entity->get_id(),
                                std::string("Entity health is critical! Call a doctor!"));
        }
        
    }
};

class DocController: public Controller {
public:
    DocController(MessageQueue* mq)
    : Controller(mq)
    {
        this->mq->subscribe(std::string("health_crit"), this);
    }
    
    void notify(std::string message){
        if (message.compare(std::string("health_crit")) == 0){
            //TODO(samstudio8) Cheated and hard coded the hoot ID...
            
            std::ostringstream oss;
            oss << "Doctor E" << this->entity->get_id() << " sends medical aid to Entity E2";
            std::string msg = oss.str();
            
            this->mq->broadcast(std::string("health_pack"), 2, this->entity->get_id(), msg);
        }
    }
    
    void tick(){}
};

int main(){

    MessageQueue mq;
    Simulator sim(&mq);
    
    SimController sc(&sim, &mq);
    sc.add_requirement("is_simulator");
    sim.register_controller(&sc);
    
    HootController hc(&mq);
    sim.register_controller(&hc);
    hc.set_id(1);
    hc.add_requirement("hooting");
    hc.add_requirement("nocturnal");
    
    DocController dc(&mq);
    sim.register_controller(&dc);
    dc.set_id(3);
    dc.add_requirement("has_doctorate");
    
    
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
    
    Entity doctor(&mq);
    sim.register_entity(&doctor);
    doctor.set_id(4);
    doctor.add_property("has_doctorate", 1);
    
    //std::cout << "\nHoot Properties:\n";
    for (std::map<std::string, float>::iterator it=hoot.get_properties().begin(); it!=hoot.get_properties().end(); ++it){
        //std::cout << it->first << " => " << it->second << '\n';
    }

    for(int i=0; i<24; i++){
        sim.tick();
        usleep(2000000);
    }
    return 0;
}