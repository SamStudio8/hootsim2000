#include <iostream>
#include <sstream>
#include <string>

#include <unistd.h>

#include "Controller.h"
#include "Entity.h"
#include "MessageQueue.h"
#include "Simulator.h"


class HootController: public Controller {
public:
    HootController(Simulator* sim)
    : Controller(sim)
    {
        this->mq->subscribe(std::string("health_pack"), this);
        this->mq->subscribe(std::string("new_dawn"), this);
        this->mq->subscribe(std::string("sim_tick"), this);
    }

    void notify(const std::string& msg_type, int to, int from, const std::string& message){
        (void)message;
        (void)from;
        (void)to;
        
        if (msg_type.compare(std::string("sim_tick")) == 0){
            
            float ATTRITION_DAMAGE_PER_UNIT = 10;
                            
            std::ostringstream oss;
            oss << "Entity E" << this->get_entity(to)->get_id() << " suffers attrition!";
            std::string msg = oss.str();
                
            this->mq->broadcast(std::string("health_loss"), -1, to, msg);
                
            float health = this->get_entity(to)->get_property("health");
            health = health - ATTRITION_DAMAGE_PER_UNIT;        
            this->get_entity(to)->update_property("health", health);
                
            if (health <= 10){
                this->mq->broadcast(std::string("health_crit"), -1, to,
                                    std::string("Entity health is critical! Call a doctor!"));
            }
        }
        else if (msg_type.compare(std::string("health_pack")) == 0){
            std::ostringstream oss;
            oss << "Entity E" << to << " health restored!";
            std::string msg = oss.str();
            this->mq->broadcast(std::string("health_okay"), -1, to, msg);
            this->get_entity(to)->update_property("health", 100);
        }
        else if (msg_type.compare(std::string("new_dawn")) == 0){

            std::ostringstream oss;
            oss << "Entity E" << to << " hoots!";
            std::string msg = oss.str();

            this->mq->broadcast(std::string("hoot_hoot"), -1, to, msg);
        }
    }

};

    
class DocController: public Controller {
public:
    DocController(Simulator* sim)
    : Controller(sim)
    {
        this->mq->subscribe(std::string("health_crit"), this);
        this->mq->subscribe(std::string("time_noon"), this);
    }

    
    void notify(const std::string& msg_type, int to, int from, const std::string& message){
        (void)message;
        (void)from;
        (void)to;
        
        //TODO Check 'to' is valid?
        
        if (msg_type.compare(std::string("health_crit")) == 0){
            std::ostringstream oss;
            oss << "Doctor E" << to << " sends medical aid to Entity E" << from;
            std::string msg = oss.str();

            this->mq->broadcast(std::string("health_pack"), from, to, msg);
        }
        else if (msg_type.compare(std::string("time_noon")) == 0){

            std::ostringstream oss;
            oss << "Doctor E" << to << " eats lunch.";
            std::string msg = oss.str();

            this->mq->broadcast(std::string("doc_noon"), -1, to, msg);
        }
    }

};

class WorldController: public Controller {
public:
    WorldController(Simulator* sim)
    : Controller(sim)
    {
        this->mq->subscribe(std::string("sim_tick"), this);
    }

    void notify(const std::string& msg_type, int to, int from, const std::string& message){
        (void)message;
        (void)from;
        (void)to;

        if (msg_type.compare(std::string("sim_tick")) == 0){

            float hour = this->get_entity(to)->get_property("time");
            hour = hour + 1;
            hour = float(int(hour) % 24);
            this->get_entity(to)->update_property("time", hour);

            std::ostringstream oss;
            oss << "World Entity E" << to << " updates hour to " << hour;
            std::string msg = oss.str();
            this->mq->broadcast(std::string("new_hour"), -1, to, msg);

            if(hour == 6){
                this->mq->broadcast(std::string("new_dawn"), -1, to, std::string("A new day dawns...")
                );
            }
            else if(hour == 12){
                this->mq->broadcast(std::string("time_noon"), -1, to,
                                    std::string("It's noon. Hope you're hungry.")
                );
            }
            else if(hour == 18){
                this->mq->broadcast(std::string("time_evening"), -1, to,
                    std::string("Better get indoors. It's getting dark.")
                );
            }
        }
    }

};

int main(){

    MessageQueue mq;
    Simulator sim(&mq);

    HootController hc(&sim);
    hc.add_requirement("hooting");
    hc.add_requirement("nocturnal");

    DocController dc(&sim);
    dc.add_requirement("has_doctorate");

    WorldController wc(&sim);
    wc.add_requirement("is_world");
    wc.add_requirement("time");

    
    Entity hoot(&sim);
    hoot.add_property("nocturnal", 1);
    hoot.add_property("hooting", 1);
    hoot.add_property("health", 100);

    Entity doctor(&sim);
    doctor.add_property("has_doctorate", 1);

    Entity world(&sim);
    world.add_property("is_world", 1);
    world.add_property("time", 0);
    
    for(int i=0; i<13; i++){
        sim.tick();
        usleep(2000000);
    }
    return 0;
}
