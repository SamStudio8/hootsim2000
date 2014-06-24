#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <string>

class Entity {
public:
    Entity();
    Entity(class MessageQueue*);
    ~Entity();
    
    std::map<std::string, float> get_properties();
    void add_property(std::string key, float value);
private:
    std::map<std::string, float> properties;
};

#endif // ENTITY_H
