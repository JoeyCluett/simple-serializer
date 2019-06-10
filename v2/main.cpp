#include <iostream>

// uncomment to enable debugging output from serializer
//#define LOG_OUTPUT
#include "main.h"

#include <serialize/serializer.h>
#include <serialize/serializable.h>

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {

    // demonstrate the polymorphic nature of the library
    vector<serializable*> ser_vec;
    ser_vec.push_back(new integer_collection(1));
    ser_vec.push_back(new float_collection(100.3f, 200.3));
    ser_vec.push_back(new mixed_collection);
    ser_vec.push_back(new array_collection(4));

    vector<int> sample_int_vector = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5 };
    vector<std::string> sample_string_vector = { 
        "hello world", 
        "nobody expects the spanish inquisition!",
        "'tis but a scratch", 
        "youre mother was a hamster",
        "an african or\n\teuropean swallow?"
    };

    serializer ser;
    ser.open_output("tmp.txt");
    ser.clear_output();

    // save each object to file
    for(auto* sptr : ser_vec) {
        sptr->serialize(ser);
        delete sptr; // get rid of these objects, they are saved to file
    }
    ser_vec.clear();

    // save integer vector to file
    ser << sample_int_vector;
    ser.end_doc();

    // save the string vector to file
    ser << sample_string_vector;
    ser.end_doc();

    sample_int_vector.clear();
    sample_string_vector.clear();

    ser.close_output();
    ser.open_input("tmp.txt");

    ser_vec.push_back(new integer_collection(0));
    ser_vec.push_back(new float_collection(0, 0));
    ser_vec.push_back(new mixed_collection());
    ser_vec.push_back(new array_collection(0));    

    // read data back in from the file
    for(auto* sptr : ser_vec)
        sptr->deserialize(ser);

    // read integer vector back in from file
    ser >> sample_int_vector;

    // read the string vector back in from file
    ser >> sample_string_vector;

    ser.close_input();

    // print the contents of the objects
    cout << *static_cast<integer_collection*>(ser_vec[0]) << endl;
    cout << *static_cast<float_collection*>(ser_vec[1]) << endl;
    cout << *static_cast<mixed_collection*>(ser_vec[2]) << endl;
    cout << *static_cast<array_collection*>(ser_vec[3]) << endl;

    for(int i = 0; i < sample_int_vector.size(); i++)
        cout << i << " : " << sample_int_vector[i] << endl;

    cout << endl;

    for(int i = 0; i < sample_string_vector.size(); i++)
        cout << i << " : " << sample_string_vector[i] << endl;


    return 0;
}

