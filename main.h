#pragma once

#include <serialize/serializer.h>
#include <serialize/serializable.h>

struct integer_collection : public serializable {

    int a, b, c, d;

    integer_collection(int a) {
        this->a = a * 1;
        this->b = a * 2;
        this->c = a * 3;
        this->d = a * 4;
    }

    friend std::ostream& operator<<(std::ostream& os, integer_collection& mcr) {
        os << "integer_collection\n";
        os << "\ta : " << mcr.a << std::endl;
        os << "\tb : " << mcr.b << std::endl;
        os << "\tc : " << mcr.c << std::endl;
        os << "\td : " << mcr.d << std::endl;
        
        return os;
    }

    // inherited from serializable
    void serialize(serializer& ser) override {
        ser << a << b << c << d;
        ser.end_doc();
    }

    void deserialize(serializer& ser) override {
        ser >> a >> b >> c >> d;
    }

};

struct float_collection : public serializable {

    float a, b;
    double c, d;

    float_collection(float a, double b) {
        this->a = 1.0f * a;
        this->b = 2.0f * a;

        this->c = 1.0 * b;
        this->d = 2.0 * b;
    }

    friend std::ostream& operator<<(std::ostream& os, float_collection& ic) {
        os << "float_collection\n";
        os << "\ta : " << ic.a << std::endl;
        os << "\tb : " << ic.b << std::endl;
        os << "\tc : " << ic.c << std::endl;
        os << "\td : " << ic.d << std::endl;
        
        return os;
    }

    void serialize(serializer& ser) override {
        ser << a << b << c << d;
        ser.end_doc();
    }

    void deserialize(serializer& ser) override {
        ser >> a >> b >> c >> d;
    }

};

struct mixed_collection : public serializable {

    float a;
    double b;
    int c;
    long int d;
    std::string e;

    mixed_collection(void) {
        this->a = 3.14159f;
        this->b = 6.28318;
        this->c = 13;
        this->d = 26;
        this->e = "Hello World";
    }

    friend std::ostream& operator<<(std::ostream& os, mixed_collection& mcr) {
        os << "mixed_collection\n";
        os << "\ta : " << mcr.a << std::endl;
        os << "\tb : " << mcr.b << std::endl;
        os << "\tc : " << mcr.c << std::endl;
        os << "\td : " << mcr.d << std::endl;
        os << "\te : " << mcr.e << std::endl;
        
        return os;
    }

    void serialize(serializer& ser) override {
        ser << a << b << c << d << e;
        ser.end_doc();
    }

    void deserialize(serializer& ser) override {
        ser >> a >> b >> c >> d >> e;
    }

};

struct array_collection : public serializable {

    int a[3];

    array_collection(int i) {
        a[0] = i * 1;
        a[1] = i * 2;
        a[2] = i * 3;
    }

    friend std::ostream& operator<<(std::ostream& os, array_collection& ac) {
        os << "array_collection\n";
        os << 
            "\ta[0] : " << ac.a[0] << std::endl << 
            "\ta[1] : " << ac.a[1] << std::endl << 
            "\ta[2] : " << ac.a[2] << std::endl;
        
        return os;
    }

    void serialize(serializer& ser) override {
        ser << INT_ARR{3, a};
        ser.end_doc();
    }

    void deserialize(serializer& ser) override {
        ser >> INT_ARR{3, a};
    }

};

