#ifndef RECEIVER_H
#define RECEIVER_H

#include <string>

#include "Registerable.h"

class Receiver: public Registerable {
public:
    virtual ~Receiver() {}
    virtual void super_notify(const std::string& msg_type, int to, int from, const std::string& message) = 0;
};

#endif // RECEIVER_H
