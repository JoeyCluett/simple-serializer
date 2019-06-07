#pragma once

#include <string>
#include <vector>
#include <iostream>

enum class Type : int {
    NONE, INT, UINT, LONG, ULONG, FLOAT, DOUBLE, STRING
};

std::ostream& operator<<(std::ostream& os, Type type);

class MultiType {
public:

    Type type;

    // places to hold possible data types
    union {
        int32_t  i32;
        uint32_t u32;
        int64_t  i64;
        uint64_t u64;
        float    f32;
        double   f64;
    };
    std::string str;

//public:

    MultiType(void);
    MultiType(int32_t i32);
    MultiType(uint32_t u32);
    MultiType(int64_t i64);
    MultiType(uint64_t u64);
    MultiType(float f32);
    MultiType(double f64);

    // two string types
    MultiType(std::string s);
    MultiType(const char* cptr);

    // copy constructor
    MultiType(const MultiType& mt);

    // returns true if tested type is the same
    bool checkType(Type t);

    // return the current type of this instance
    Type getType(void);

    // convenient way to print the contents of this MultiType
    friend std::ostream& operator<<(std::ostream& os, MultiType& mt);

};
