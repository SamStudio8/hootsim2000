#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <string>

class Entity {
public:
    Entity();
    ~Entity();
    
    std::map<std::string, float> get_properties();
private:
    std::map<std::string, float> properties;
};

#endif // ENTITY_H
