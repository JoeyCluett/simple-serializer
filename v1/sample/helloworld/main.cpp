#include <iostream>
#include <MultiType.h>
#include <Document.h>
#include <Database.h>

using namespace std;

int main(int argc, char* argv[]) {

    MultiType mt(13L);
    cout << mt << endl;

    mt = 14.0;
    cout << mt << endl;

    mt = mt;
    cout << mt << endl;

    mt = "Hello World";
    cout << mt << endl;

    Database db({ Type::INT, Type::LONG, Type::STRING }, "db/simpledb.txt");

    {
        Document d({ 
            1, 
            13L, 
            "hello world" 
        });

        db.addDocument();

    }

    return 0;
}
