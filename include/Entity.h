#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <string>

class Entity {
public:
    Entity();
    Entity(class MessageQueue* mq);
    ~Entity();
    
    int get_id();
    void set_id(int id);
    
    std::map<std::string, float> get_properties();
    void add_property(const std::string& key, float value);
    float get_property(const std::string& key);
    void update_property(const std::string& key, float value);
private:
    int id;
    class MessageQueue* mq;
    std::map<std::string, float> properties;
};

#endif // ENTITY_H
