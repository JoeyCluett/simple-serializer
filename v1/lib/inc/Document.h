#pragma once

#include <MultiType.h>
#include <vector>
#include <initializer_list>
#include <string>

class Document {
private:

    std::vector<MultiType> data_vec;

public:
    
    // populates a Document with data from a database file
    Document(std::vector<Type>& format, std::ifstream& ifs);

    // constructor takes explicit description of contents on Document
    Document(std::vector<MultiType> doc);

    std::vector<Type> getDesc(void);
    std::vector<MultiType>& data(void);
    friend std::ostream& operator<<(std::ostream& os, const Document& doc);

};

