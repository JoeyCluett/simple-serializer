#include <MultiType.h>
#include <iostream>

MultiType::MultiType(void) {
    this->type = Type::NONE;
}

MultiType::MultiType(int32_t i32) {
    this->type = Type::INT;
    this->i32 = i32;
}

MultiType::MultiType(uint32_t u32) {
    this->type = Type::UINT;
    this->u32 = u32;
}

MultiType::MultiType(int64_t i64) {
    this->type = Type::LONG;
    this->i64 = i64;
}

MultiType::MultiType(uint64_t u64) {
    this->type = Type::ULONG;
    this->u64 = u64;
}

MultiType::MultiType(float f32) {
    this->type = Type::FLOAT;
    this->f32 = f32;
}

MultiType::MultiType(double f64) {
    this->type = Type::DOUBLE;
    this->f64 = f64;
}

MultiType::MultiType(std::string s) {
    this->type = Type::STRING;
    this->str = s;
}

MultiType::MultiType(const char* cptr) {
    this->type = Type::STRING;
    this->str = cptr;
}

// copy constructor
MultiType::MultiType(const MultiType& mt) {

    //std::cout << "Copy constructor\n";

    //auto t = mt.getType();
    auto t = mt.type;
    this->type = t;

    switch(t) {
        case Type::INT:
        case Type::UINT:
        case Type::LONG:
        case Type::ULONG:
        case Type::FLOAT:
        case Type::DOUBLE:
            this->f64 = mt.f64;
            break;
        case Type::STRING:
            this->str = mt.str;
            break;
        case Type::NONE:
        default:
            break;
    }
}

Type MultiType::getType(void) {
    return this->type;
}

bool MultiType::checkType(Type t) {
    return (t == this->type);
}

std::ostream& operator<<(std::ostream& os, MultiType& mt) {

    switch(mt.type) {
        case Type::INT:
            os << "[int] " << mt.i32; break;
        case Type::UINT:
            os << "[uint] " << mt.u32; break;
        case Type::LONG:
            os << "[long] " << mt.i64; break;
        case Type::ULONG:
            os << "[ulong] " << mt.u64; break;
        case Type::FLOAT:
            os << "[float] " << mt.f32; break;
        case Type::DOUBLE:
            os << "[double] " << mt.f64; break;
        case Type::STRING:
            os << "[string] " << (mt.str.size() ? mt.str : "<empty>"); break;
        case Type::NONE:
            os << "[NONE] "; break;
        default:
            throw std::runtime_error("MultiType::operator<< : unknown type");
            break;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, Type type) {
    switch(type) {
        case Type::NONE:   os << "[NONE]";   break;
        case Type::INT:    os << "[INT]";    break;
        case Type::UINT:   os << "[UINT]";   break;
        case Type::LONG:   os << "[LONG]";   break;
        case Type::ULONG:  os << "[ULONG]";  break;
        case Type::STRING: os << "[STRING]"; break;
    }

    return os;
}
