#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TUPLE_SIZE 5

void convertTupleStringToIntTuple(const char* tupleString, int* intTuple, size_t tupleSize) {
    char temp[tupleSize * 2 + 1];
    strcpy(temp, tupleString);

    char* token;
    token = strtok(temp, ",");

    for (size_t i = 0; i < tupleSize && token != NULL; i++) {
        long numToken = atol(token);
        
        if (numToken <= INT_MAX && numToken >= INT_MIN) {
            intTuple[i] = (int) numToken;
        } else {
            // Handle the error appropriately
            exit(EXIT_FAILURE);
        }

        token = strtok(NULL, ",");
    }
}

int main() {
    const char tupleString[] = "1,2,3,4,5";
    int intTuple[TUPLE_SIZE] = {0};

    convertTupleStringToIntTuple(tupleString, intTuple, TUPLE_SIZE);

    for (size_t i = 0; i < TUPLE_SIZE; i++) {
        printf("%d ", intTuple[i]);
    }

    return 0;
}