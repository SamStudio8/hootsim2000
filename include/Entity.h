#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <string>

#include "Registerable.h"

class Entity: public Registerable {
public:
    Entity();
    Entity(class Simulator* sim);
    ~Entity();
    
    std::map<std::string, float> get_properties();
    void add_property(const std::string& key, float value);
    float get_property(const std::string& key);
    void update_property(const std::string& key, float value);
    
private:
    std::map<std::string, float> properties;
};

#endif // ENTITY_H
