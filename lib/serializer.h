#pragma once

#include <fstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>
#include <sstream>
#include <functional>

// UUID support
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

typedef boost::uuids::uuid               uuid_t;
typedef boost::uuids::random_generator   uuid_gen_t;

typedef std::pair<int, int*>         INT_ARR;
typedef std::pair<int, long int*>    LONG_ARR;
typedef std::pair<int, std::string*> STRING_ARR;
typedef std::pair<int, float*>       FLOAT_ARR;
typedef std::pair<int, double*>      DOUBLE_ARR;

class serializer : public std::ostream , public std::istream {
private:

    std::ifstream input;
    std::ofstream output;

    std::string input_name;
    std::string output_name;

    static uuid_gen_t gen;

public:

    serializer(void);

    static uuid_t new_uuid(void);

    // output configuration methods
    void open_output(std::string str);

    void clear_output(void);

    void close_output(void);

    // input configuration methods
    void open_input(std::string str);

    void close_input(void);

    // end of each document

    void end_doc(void);

    friend serializer& operator<<(serializer& ser, std::ostream& (*_pf)(std::ostream&));

    // UUID support methods
    friend serializer& operator<<(serializer& ser, uuid_t& uuid);
    friend serializer& operator>>(serializer& ser, uuid_t& uuid);

    //
    // serialize methods
    //

    friend serializer& operator<<(serializer& ser, int data);
    friend serializer& operator<<(serializer& ser, long int data);
    friend serializer& operator<<(serializer& ser, std::string& data);
    friend serializer& operator<<(serializer& ser, float data);
    friend serializer& operator<<(serializer& ser, double data);

    //
    // deserialize methods
    //

    friend serializer& operator>>(serializer& ser, int& data);
    friend serializer& operator>>(serializer& ser, long int& data);
    friend serializer& operator>>(serializer& ser, std::string& data);
    friend serializer& operator>>(serializer& ser, float& data);
    friend serializer& operator>>(serializer& ser, double& data);

    //
    // serialize array methods
    //

    friend serializer& operator<<(serializer& ser, std::pair<int, int*> data);
    friend serializer& operator<<(serializer& ser, std::pair<int, long int*> data);
    friend serializer& operator<<(serializer& ser, std::pair<int, std::string*> data);
    friend serializer& operator<<(serializer& ser, std::pair<int, float*> data);
    friend serializer& operator<<(serializer& ser, std::pair<int, double*> data);

    //
    // deserialize array methods
    //

    friend serializer& operator>>(serializer& ser, std::pair<int, int*> data);
    friend serializer& operator>>(serializer& ser, std::pair<int, long int*> data);
    friend serializer& operator>>(serializer& ser, std::pair<int, std::string*> data);
    friend serializer& operator>>(serializer& ser, std::pair<int, float*> data);
    friend serializer& operator>>(serializer& ser, std::pair<int, double*> data);

    //
    // serialize vector methods
    //

    friend serializer& operator<<(serializer& ser, std::vector<int>& data);
    friend serializer& operator<<(serializer& ser, std::vector<long int>& data);
    friend serializer& operator<<(serializer& ser, std::vector<std::string>& data);
    friend serializer& operator<<(serializer& ser, std::vector<float>& data);
    friend serializer& operator<<(serializer& ser, std::vector<double>& data);

    //
    // deserialize vector methods
    //

    friend serializer& operator>>(serializer& ser, std::vector<int>& data);
    friend serializer& operator>>(serializer& ser, std::vector<long int>& data);
    friend serializer& operator>>(serializer& ser, std::vector<std::string>& data);
    friend serializer& operator>>(serializer& ser, std::vector<float>& data);
    friend serializer& operator>>(serializer& ser, std::vector<double>& data);

};

uuid_gen_t serializer::gen = uuid_gen_t();
