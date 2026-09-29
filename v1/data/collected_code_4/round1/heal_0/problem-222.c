#include <stdio.h>
#include <stdbool.h>

#define INT_TYPE    0
#define FLOAT_TYPE  1
#define CHAR_TYPE   2

void* myTuple[3];
int   myTupleTypes[3];

bool checkIfAllElementsSameType(void** tuple, int* dataTypes, int tupleSize)
{
    int i;
    for(i = 1; i < tupleSize; i++)
    {
        if(dataTypes[i] != dataTypes[0])
            return false;
    }
    return true;
}

int main()
{
    int a = 5, b = 10, c = 15;
    float f = 2.5f;

    myTuple[0] = &a;
    myTuple[1] = &b;
    myTuple[2] = &c;

    myTupleTypes[0] = INT_TYPE;
    myTupleTypes[1] = INT_TYPE;
    myTupleTypes[2] = INT_TYPE;

    printf("Are all elements of same type: %s\n", checkIfAllElementsSameType(myTuple, myTupleTypes, 3)?"Yes":"No");

    myTuple[2] = &f;
    myTupleTypes[2] = FLOAT_TYPE;

    printf("Are all elements of same type: %s\n", checkIfAllElementsSameType(myTuple, myTupleTypes, 3)?"Yes":"No");

    return 0;
} 