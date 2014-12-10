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

    void notify(const std::string& message){
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
        this->set_id(1);
        this->mq->subscribe(std::string("health_pack"), this);
        this->mq->subscribe(std::string("new_dawn"), this);
    }

    void notify(const std::string& message){
        if (message.compare(std::string("health_pack")) == 0){
            std::ostringstream oss;
            oss << "Entity E" << this->entity->get_id() << " health restored!";
            std::string msg = oss.str();
            this->mq->broadcast(std::string("health_okay"), -1, this->entity->get_id(), msg);
            this->entity->update_property("health", 100);
        }
        else if (message.compare(std::string("new_dawn")) == 0){

            std::ostringstream oss;
            oss << "Entity E" << this->entity->get_id() << " hoots!";
            std::string msg = oss.str();

            this->mq->broadcast(std::string("hoot_hoot"), -1, this->entity->get_id(), msg);
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
        this->set_id(3);
        this->mq->subscribe(std::string("health_crit"), this);
        this->mq->subscribe(std::string("time_noon"), this);
    }

    void notify(const std::string& message){
        if (message.compare(std::string("health_crit")) == 0){
            //TODO(samstudio8) Cheated and hard coded the hoot ID...

            std::ostringstream oss;
            oss << "Doctor E" << this->entity->get_id() << " sends medical aid to Entity E2";
            std::string msg = oss.str();

            this->mq->broadcast(std::string("health_pack"), 2, this->entity->get_id(), msg);
        }
        else if (message.compare(std::string("time_noon")) == 0){

            std::ostringstream oss;
            oss << "Doctor E" << this->entity->get_id() << " eats lunch.";
            std::string msg = oss.str();

            this->mq->broadcast(std::string("doc_noon"), -1, this->entity->get_id(), msg);
        }
    }

    void tick(){}
};

class WorldController: public Controller {
public:
    WorldController(MessageQueue* mq)
    : Controller(mq)
    {
        this->set_id(5);
        this->mq->subscribe(std::string("sim_tick"), this);
    }

    void notify(const std::string& message){
        if (message.compare(std::string("sim_tick")) == 0){

            float hour = this->entity->get_property("time");
            hour = hour + 1;
            hour = float(int(hour) % 24);
            this->entity->update_property("time", hour);

            std::ostringstream oss;
            oss << "World Entity E" << this->entity->get_id() << " updates hour to " << hour;
            std::string msg = oss.str();
            this->mq->broadcast(std::string("new_hour"), -1, this->entity->get_id(), msg);

            if(hour == 6){
                this->mq->broadcast(std::string("new_dawn"), -1, this->entity->get_id(),
                                    std::string("A new day dawns...")
                );
            }
            else if(hour == 12){
                this->mq->broadcast(std::string("time_noon"), -1, this->entity->get_id(),
                                    std::string("It's noon. Hope you're hungry.")
                );
            }
            else if(hour == 18){
                this->mq->broadcast(std::string("time_evening"), -1, this->entity->get_id(),
                    std::string("Better get indoors. It's getting dark.")
                );
            }
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
    hc.add_requirement("hooting");
    hc.add_requirement("nocturnal");

    DocController dc(&mq);
    sim.register_controller(&dc);
    dc.add_requirement("has_doctorate");

    WorldController wc(&mq);
    sim.register_controller(&wc);
    wc.add_requirement("is_world");
    wc.add_requirement("time");


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

    Entity world(&mq);
    sim.register_entity(&world);
    world.set_id(6);
    world.add_property("is_world", 1);
    world.add_property("time", 0);

    for(int i=0; i<13; i++){
        sim.tick();
        usleep(2000000);
    }
    return 0;
}
