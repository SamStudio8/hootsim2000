#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <map>

class Simulator {
public:
    Simulator();
    ~Simulator();
private:
    std::vector<class Entity*> registered_entities;
    std::vector<class Controller*> registered_controllers;
    std::map<class Entity*, class Controller*> controllers;
};

#endif // SIMULATOR_H
