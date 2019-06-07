#pragma once

#include <fstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

typedef std::pair<int, int*>         INT_ARR;
typedef std::pair<int, long int*>    LONG_ARR;
typedef std::pair<int, std::string*> STRING_ARR;
typedef std::pair<int, float*>       FLOAT_ARR;
typedef std::pair<int, double*>      DOUBLE_ARR;

class serializer {
private:

    std::ifstream input;
    std::ofstream output;

    std::string input_name;
    std::string output_name;

public:

    serializer(void) { }

    // output configuration methods
    void open_output(std::string str) { 
        this->output.open(str, std::ios::app); 
        this->output_name = str; 
    }
    
    void clear_output(void) {
        this->output.close();
        this->output.open(this->output_name, std::ios::trunc);
    }

    void close_output(void) { this->output.close(); }
    
    // input configuration methods
    void open_input(std::string str) { 
        this->input.open(str, std::ios::in); 
        this->input_name = str; 
    }
    
    void close_input(void) { this->input.close(); }

    // end of each document

    void end_doc(void) {
        output << std::endl;
    }

    //
    // serialize methods
    //

    friend serializer& operator<<(serializer& ser, int data) {
        ser.output << data << ' ';
        return ser;
    }

    friend serializer& operator<<(serializer& ser, long int data) {
        ser.output << data << ' ';
        return ser;
    }

    friend serializer& operator<<(serializer& ser, std::string& data) {
        // need to encode whitespace a lil differently
        for(char c : data) {
            switch(c) {
                case ' ':  ser.output << "\\s"; break;
                case '\n': ser.output << "\\n"; break;
                case '\t': ser.output << "\\t"; break;
                case '\\': ser.output << "\\\\"; break;
                default:
                    ser.output << c; break;
            }
        }

        ser.output << ' ';
        return ser;
    }

    friend serializer& operator<<(serializer& ser, float data) {
        ser.output << std::fixed << std::setprecision(7) << data << ' ';
        return ser;
    }

    friend serializer& operator<<(serializer& ser, double data) {
        ser.output << std::fixed << std::setprecision(14) << data << ' ';
        return ser;
    }

    //
    // deserialize methods
    //

    friend serializer& operator>>(serializer& ser, int& data) {
        ser.input >> data;

        #ifdef LOG_OUTPUT
        std::cout << "[DES] Log: " << data << std::endl;
        #endif

        return ser;
    }

    friend serializer& operator>>(serializer& ser, long int& data) {
        ser.input >> data;

        #ifdef LOG_OUTPUT
        std::cout << "[DES] Log: " << data << std::endl;
        #endif

        return ser;
    }

    friend serializer& operator>>(serializer& ser, std::string& data) {
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

    friend serializer& operator>>(serializer& ser, float& data) {
        ser.input >> data;

        #ifdef LOG_OUTPUT
        std::cout << "[DES] Log: " << data << std::endl;
        #endif

        return ser;
    }

    friend serializer& operator>>(serializer& ser, double& data) {
        ser.input >> data;

        #ifdef LOG_OUTPUT
        std::cout << "[DES] Log: " << data << std::endl;
        #endif

        return ser;
    }

    //
    // serialize array methods
    //

    friend serializer& operator<<(serializer& ser, std::pair<int, int*> data) {
        for(int i = 0; i < data.first; i++)
            ser << *(data.second + i);
        ser.end_doc();
    
        return ser;
    }

    friend serializer& operator<<(serializer& ser, std::pair<int, long int*> data) {
        for(int i = 0; i < data.first; i++)
            ser << *(data.second + i);
        ser.end_doc();
    
        return ser;
    }

    friend serializer& operator<<(serializer& ser, std::pair<int, std::string*> data) {
        for(int i = 0; i < data.first; i++)
            ser << *(data.second + i);
        ser.end_doc();
    
        return ser;
    }

    friend serializer& operator<<(serializer& ser, std::pair<int, float*> data) {
        for(int i = 0; i < data.first; i++)
            ser << *(data.second + i);
        ser.end_doc();
    
        return ser;
    }

    friend serializer& operator<<(serializer& ser, std::pair<int, double*> data) {
        for(int i = 0; i < data.first; i++)
            ser << *(data.second + i);
        ser.end_doc();
    
        return ser;
    }

    //
    // deserialize array methods
    //

    friend serializer& operator>>(serializer& ser, std::pair<int, int*> data) {
        for(int i = 0; i < data.first; i++)
            ser >> *(data.second + i);
        return ser;
    }

    friend serializer& operator>>(serializer& ser, std::pair<int, long int*> data) {
        for(int i = 0; i < data.first; i++)
            ser >> *(data.second + i);
        return ser;
    }

    friend serializer& operator>>(serializer& ser, std::pair<int, std::string*> data) {
        for(int i = 0; i < data.first; i++)
            ser >> *(data.second + i);
        return ser;
    }

    friend serializer& operator>>(serializer& ser, std::pair<int, float*> data) {
        for(int i = 0; i < data.first; i++)
            ser >> *(data.second + i);
        return ser;
    }

    friend serializer& operator>>(serializer& ser, std::pair<int, double*> data) {
        for(int i = 0; i < data.first; i++)
            ser >> *(data.second + i);
        return ser;
    }

    //
    // serialize vector methods
    //

    friend serializer& operator<<(serializer& ser, std::vector<int>& data) {
        ser << (long int)data.size();

        for(auto& d : data)
            ser << d;

        return ser;
    }

    friend serializer& operator<<(serializer& ser, std::vector<long int>& data) {
        ser << (long int)data.size();

        for(auto& d : data)
            ser << d;

        return ser;
    }
    
    friend serializer& operator<<(serializer& ser, std::vector<std::string>& data) {
        ser << (long int)data.size();

        for(auto& d : data)
            ser << d;

        return ser;
    }
    
    friend serializer& operator<<(serializer& ser, std::vector<float>& data) {
        ser << (long int)data.size();

        for(auto& d : data)
            ser << d;

        return ser;
    }

    friend serializer& operator<<(serializer& ser, std::vector<double>& data) {
        ser << (long int)data.size();

        for(auto& d : data)
            ser << d;

        return ser;
    }

    //
    // deserialize vector methods
    //

    friend serializer& operator>>(serializer& ser, std::vector<int>& data) {
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

    friend serializer& operator>>(serializer& ser, std::vector<std::string>& data) {
        long int sz;
        ser >> sz;
        data.clear();

        for(int i = 0; i < sz; i++) {
            std::string tmp;
            ser >> tmp;
            data.push_back(tmp);
        }

        return ser;
    }

};
