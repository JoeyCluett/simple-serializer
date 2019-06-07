#pragma once

#include <MultiType.h>
#include <Document.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Database {
private:

    // database maintains this information until it is destroyed
    std::vector<Type> format;
    std::map<long int, Document> data;
    std::string filename;
    int next_tag;

    // formats the database file with the proper information
    void formatNewFile(std::vector<Type>& format, std::string& filename);

    // reads an existing database. By this point, the database file definitely exists
    void readFileData(std::string& filename);

    // strings work a bit differently than regular primitives
    void writeStringToDbFile(std::ofstream& ofs, std::string& str);)

public:

    // doesnt assume the database already exists. if it doesnt, it is created.
    // uses boost::filesystem to check for existance
    Database(std::vector<Type> format, std::string filename);

    // looks for an existing database file with the given name. throws exception if database does not exist
    Database(std::string filename);

    // saves data to database file
    ~Database(void);

    // add a document to the database
    void addNewDocument(Document doc);

};



