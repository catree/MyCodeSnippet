#include <string>
using namespace std;


#ifndef CREATE_AND_DESTROY_H
#define CREATE_AND_DESTROY_H

class CreateAndDestroy
{
public:
    CreateAndDestroy(int, string);
    ~CreateAndDestroy();
private:
    int objectID;
    string message;
};

#endif