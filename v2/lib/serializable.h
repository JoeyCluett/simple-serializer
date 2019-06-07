#pragma once

#include <fstream>
#include "serializer.h"

class serializable {
public:

    virtual void serialize(serializer& ser) = 0;   // pure virtual function
    virtual void deserialize(serializer& ser) = 0; // ...

};



