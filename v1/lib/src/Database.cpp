#include <Database.h>
#include <Document.h>
#include <MultiType.h>

#include <boost/filesystem.hpp>

Database::Database(std::vector<Type> format, std::string filename) {
    if(!boost::filesystem::exists(filename.c_str())) {
        std::cout << "Formatting new database file...";
        this->formatNewFile(format, filename);
        std::cout << "DONE\n";
    }

    this->filename = filename;
    this->readFileData(filename);
}

Database::Database(std::string filename) {
    if(!boost::filesystem::exists(filename.c_str()))
        throw std::runtime_error("Database file does not exist");

    this->filename = filename;
    this->readFileData(filename);
}

// write the contents of the data base to the file
Database::~Database(void) {
    std::ofstream ofs(this->name, std::ios::out);

    for(auto& doc : this->data) {
        for(auto& rec: doc.data()) {
            switch(rec.type) {
                case Type::NONE:
                    throw std::runtime_error("");
                case Type::INT:
                case Type::UINT:
                case Type::LONG:
                case Type::ULONG:
                case Type::STRING:
                default:
                    break;
            }
        }
    }

    ofs.close();
}

void Database::writeStringToDbFile(std::ofstream& ofs, std::string& str) {
    std::vector<char> temp;

    for(char c : str) {
        switch(c) {
            case ' ':
                temp.push_back('\\');
                temp.push_back('s');
                break;
            case '\n':
                temp.push_back('\\');
                temp.push_back('n');
                break;
            case '\t':
                temp.push_back('\\');
                temp.push_back('t');
                break;
            case '\\':
                temp.push_back('\\');
                temp.push_back('\\');
                break;
            default:
                temp.push_back(c);
                break;
        }
    }

    temp.push_back('\0');
    ofs << &temp[0] << ' ';

}


void Database::formatNewFile(std::vector<Type>& format, std::string& filename) {

    std::ofstream of(filename, std::ios::out);

    std::vector<char> format_string;
    for(auto t : format) {
        switch(t) {
            case Type::NONE:   throw std::runtime_error("NONE type not allowed in database file"); break;
            case Type::INT:    format_string.push_back('i'); break;
            case Type::UINT:   format_string.push_back('I'); break;
            case Type::LONG:   format_string.push_back('l'); break;
            case Type::ULONG:  format_string.push_back('L'); break;
            case Type::FLOAT:  format_string.push_back('f'); break;
            case Type::DOUBLE: format_string.push_back('F'); break;
            case Type::STRING: format_string.push_back('s'); break;
            default: throw std::runtime_error("Unrecognized type in format list"); break;
        }
    }

    format_string.push_back('\0');
    of << &format_string[0] << " 0\n";
    of.close();
}

void Database::readFileData(std::string& filename) {
    this->format.clear();

    std::ifstream ifs(filename, std::ios::in);
    std::string current_input;

    ifs >> current_input;
    if(current_input.size() == 0)
        throw std::runtime_error("Database file is missing formatting information");

    // generate format information from format string
    for(char c : current_input) {
        switch(c) {
            case 'i': this->format.push_back(Type::INT);    break;
            case 'I': this->format.push_back(Type::UINT);   break;
            case 'l': this->format.push_back(Type::LONG);   break;
            case 'L': this->format.push_back(Type::ULONG);  break;
            case 'f': this->format.push_back(Type::FLOAT);  break;
            case 'F': this->format.push_back(Type::DOUBLE); break;
            case 's': this->format.push_back(Type::STRING); break;
            default: throw std::runtime_error("Unrecognized character in database format string");
        }
    }

    std::cout << "Database format string: " << current_input << std::endl;
    std::cout << "Format information:\n";
    for(auto info : this->format)
        std::cout << "    " << info << std::endl;

    ifs >> this->next_tag;
    std::cout << "Next tag: " << this->next_tag << std::endl;

    long int tag;
    while((ifs >> tag)) {
        data.emplace_back(this->format, ifs);
    }

    ifs.close();
}

void Document::addNewDocument(Document doc) {
    // only properly formatted data is allowed in the database
    if(doc.getDesc() != this->format)
        throw std::runtime_error("Format of new document does not match existing database format");

    // make document with current tag and increment tag for next document
    this->data[this->next_tag] = doc;
    this->next_tag++;
}
