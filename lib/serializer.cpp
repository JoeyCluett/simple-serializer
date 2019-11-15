#include "serializer.h"
#include <iostream>

serializer::serializer(void) { ; }

uuid_t serializer::new_uuid(void) { return serializer::gen(); }

// output configuration methods
void serializer::open_output(std::string str) {
    this->output.open(str, std::ios::app);
    this->output_name = str;
}

void serializer::clear_output(void) {
    this->output.close();
    this->output.open(this->output_name, std::ios::trunc);
}

void serializer::close_output(void) { this->output.close(); }

// input configuration methods
void serializer::open_input(std::string str) {
    this->input.open(str, std::ios::in);
    this->input_name = str;
}

void serializer::close_input(void) { this->input.close(); }

// end of each document

void serializer::end_doc(void) {
    output << std::endl;
}

serializer& operator<<(serializer& ser, std::ostream& (*_pf)(std::ostream&)) {
    ser.output << _pf;
    return ser;
}

//
// uuid methods
//

serializer& operator<<(serializer& ser, uuid_t& uuid) {
    ser.output << uuid << ' ';
    return ser;
}

serializer& operator>>(serializer& ser, uuid_t& uuid) {
    ser.input >> uuid;
    return ser;
}

//
// serialize methods
//

serializer& operator<<(serializer& ser, int data) {
    ser.output << data << ' ';
    return ser;
}

serializer& operator<<(serializer& ser, long int data) {
    ser.output << data << ' ';
    return ser;
}

serializer& operator<<(serializer& ser, std::string& data) {

    std::stringstream ss;

    // need to encode whitespace a lil differently
    for(char c : data) {
        switch(c) {
            case ' ':  ss << "\\s"; break;
            case '\n': ss << "\\n"; break;
            case '\t': ss << "\\t"; break;
            case '\\': ss << "\\\\"; break;
            default:
                ss << c; break;
        }
    }

    ser.output << ss.str();
    return ser;
}

serializer& operator<<(serializer& ser, float data) {
    ser.output << std::fixed << std::setprecision(7) << data << ' ';
    return ser;
}

serializer& operator<<(serializer& ser, double data) {
    ser.output << std::fixed << std::setprecision(14) << data << ' ';
    return ser;
}

//
// deserialize methods
//

serializer& operator>>(serializer& ser, int& data) {
    ser.input >> data;

    #ifdef LOG_OUTPUT
    std::cout << "[DES] Log: " << data << std::endl;
    #endif

    return ser;
}

serializer& operator>>(serializer& ser, long int& data) {
    ser.input >> data;

    #ifdef LOG_OUTPUT
    std::cout << "[DES] Log: " << data << std::endl;
    #endif

    return ser;
}

serializer& operator>>(serializer& ser, std::string& data) {
    std::string tmp;
    ser.input >> tmp;

    data.clear();

    const int state_default = 0;
    const int state_special = 1;
    int state_current = state_default;

    for(char c : tmp) {
        switch(state_current) {
            case state_default:
                if(c == '\\') {
                    state_current = state_special;
                    break;
                }
                else {
                    data.push_back(c);
                }
                break;
            case state_special:
                switch(c) {
                    case 'n':  data.push_back('\n'); break;
                    case 't':  data.push_back('\t'); break;
                    case '\\': data.push_back('\\'); break;
                    case 's':  data.push_back(' '); break;
                    default:
                        throw std::runtime_error("Unrecognized special character");
                }
                state_current = state_default;
                break;
            default:
                throw std::runtime_error("Unknown state in serializer>>std::string&");
                break;
        }
    }

    #ifdef LOG_OUTPUT
    std::cout << "[DES] Log: " << data << std::endl;
    #endif

    return ser;
}

serializer& operator>>(serializer& ser, float& data) {
    ser.input >> data;

    #ifdef LOG_OUTPUT
    std::cout << "[DES] Log: " << data << std::endl;
    #endif

    return ser;
}

serializer& operator>>(serializer& ser, double& data) {
    ser.input >> data;

    #ifdef LOG_OUTPUT
    std::cout << "[DES] Log: " << data << std::endl;
    #endif

    return ser;
}

//
// serialize array methods
//

serializer& operator<<(serializer& ser, std::pair<int, int*> data) {
    for(int i = 0; i < data.first; i++)
        ser << *(data.second + i);
    ser.end_doc();

    return ser;
}

serializer& operator<<(serializer& ser, std::pair<int, long int*> data) {
    for(int i = 0; i < data.first; i++)
        ser << *(data.second + i);
    ser.end_doc();

    return ser;
}

serializer& operator<<(serializer& ser, std::pair<int, std::string*> data) {
    for(int i = 0; i < data.first; i++)
        ser << *(data.second + i);
    ser.end_doc();

    return ser;
}

serializer& operator<<(serializer& ser, std::pair<int, float*> data) {
    for(int i = 0; i < data.first; i++)
        ser << *(data.second + i);
    ser.end_doc();

    return ser;
}

serializer& operator<<(serializer& ser, std::pair<int, double*> data) {
    for(int i = 0; i < data.first; i++)
        ser << *(data.second + i);
    ser.end_doc();

    return ser;
}

//
// deserialize array methods
//

serializer& operator>>(serializer& ser, std::pair<int, int*> data) {
    for(int i = 0; i < data.first; i++)
        ser >> *(data.second + i);
    return ser;
}

serializer& operator>>(serializer& ser, std::pair<int, long int*> data) {
    for(int i = 0; i < data.first; i++)
        ser >> *(data.second + i);
    return ser;
}

serializer& operator>>(serializer& ser, std::pair<int, std::string*> data) {
    for(int i = 0; i < data.first; i++)
        ser >> *(data.second + i);
    return ser;
}

serializer& operator>>(serializer& ser, std::pair<int, float*> data) {
    for(int i = 0; i < data.first; i++)
        ser >> *(data.second + i);
    return ser;
}

serializer& operator>>(serializer& ser, std::pair<int, double*> data) {
    for(int i = 0; i < data.first; i++)
        ser >> *(data.second + i);
    return ser;
}

//
// serialize vector methods
//

serializer& operator<<(serializer& ser, std::vector<int>& data) {
    ser << (long int)data.size();

    for(auto& d : data)
        ser << d;

    return ser;
}

serializer& operator<<(serializer& ser, std::vector<long int>& data) {
    ser << (long int)data.size();

    for(auto& d : data)
        ser << d;

    return ser;
}

serializer& operator<<(serializer& ser, std::vector<std::string>& data) {
    ser << (long int)data.size();

    for(auto& d : data)
        ser << d;

    return ser;
}

serializer& operator<<(serializer& ser, std::vector<float>& data) {
    ser << (long int)data.size();

    for(auto& d : data)
        ser << d;

    return ser;
}

serializer& operator<<(serializer& ser, std::vector<double>& data) {
    ser << (long int)data.size();

    for(auto& d : data)
        ser << d;

    return ser;
}

//
// deserialize vector methods
//

serializer& operator>>(serializer& ser, std::vector<int>& data) {
    long int sz;
    ser >> sz;
    data.clear();

    for(int i = 0; i < sz; i++) {
        int tmp;
        ser >> tmp;
        data.push_back(tmp);
    }

    return ser;
}

serializer& operator>>(serializer& ser, std::vector<long int>& data) {
    long int sz;
    ser >> sz;
    data.clear();

    for(int i = 0; i < sz; i++) {
        long int tmp;
        ser >> tmp;
        data.push_back(tmp);
    }

    return ser;
}

serializer& operator>>(serializer& ser, std::vector<std::string>& data) {
    long int sz;
    ser >> sz;
    data.clear();

    std::string tmp;

    for(int i = 0; i < sz; i++) {
        ser >> tmp;
        data.push_back(tmp);
    }

    return ser;
}

serializer& operator>>(serializer& ser, std::vector<float>& data) {
    long int sz;
    ser >> sz;
    data.clear();

    for(int i = 0; i < sz; i++) {
        float tmp;
        ser >> tmp;
        data.push_back(tmp);
    }

    return ser;
}

serializer& operator>>(serializer& ser, std::vector<double>& data) {
    long int sz;
    ser >> sz;
    data.clear();

    for(int i = 0; i < sz; i++) {
        double tmp;
        ser >> tmp;
        data.push_back(tmp);
    }

    return ser;
}
