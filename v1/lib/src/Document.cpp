#include <Document.h>
#include <MultiType.h>

Document::Document(std::vector<MultiType> doc) {
    for(auto& d : doc) {
        this->data_vec.push_back(d);
    }
}

Document::Document(std::vector<Type>& format, std::ifstream& ifs) {
    for(auto& r : format) {
        MultiType mt;
        mt.type = r;
        
        switch(r) {
            case Type::NONE:
                throw std::runtime_error("Invalid type in format vector");
                break;
            case Type::INT:    ifs >> mt.i32; break;
            case Type::UINT:   ifs >> mt.u32; break;
            case Type::LONG:   ifs >> mt.i64; break;
            case Type::ULONG:  ifs >> mt.u64; break;
            case Type::STRING: ifs >> mt.str; break; // still have to "unformat" this string but this will be good enough
            default:
                throw std::runtime_error("Unrecognized type in format vector"); 
                break;
        }

        this->data_vec.push_back(mt);
    }
}

auto Document::getDesc(void) -> std::vector<Type> {
    std::vector<Type> desc;

    // this type info should really just be stored in the Document to begin with
    for(auto i : this->data_vec)
        desc.push_back(i.type);
    return desc;
}

auto Document::data(void) -> std::vector<MultiType>& {
    return this->data_vec;
}

std::ostream& operator<<(std::ostream& os, const Document& doc) {

    os << "Size: " << doc.data_vec.size() << std::endl;

    for(auto i : doc.data_vec)
        os << i << std::endl;

    return os;
}


