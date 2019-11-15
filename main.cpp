#include <iostream>

// uncomment to enable debugging output from serializer
//#define LOG_OUTPUT
#include "main.h"

#include <serialize/serializer.h>
#include <serialize/serializable.h>

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {

    customer_t c[3];

    for(int i = 0; i < 3; i++)
        c[i].uuid = serializer::new_uuid();

    c[0].firstname = "Joe";
    c[0].lastname  = "Cluett";

    c[1].firstname = "John";
    c[1].lastname  = "Doe";

    c[2].firstname = "Jane";
    c[2].lastname  = "Doe";

    return 0;
}
