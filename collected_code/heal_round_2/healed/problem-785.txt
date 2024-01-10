#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TUPLE_SIZE 5
#define BUFFER_SIZE (TUPLE_SIZE * 2 + 1)

void convertTupleStringToIntTuple(const char* tupleString, int* intTuple, size_t tupleSize) {
    char temp[BUFFER_SIZE];

    if (strlen(tupleString) >= BUFFER_SIZE) {
        exit(EXIT_FAILURE);
    }

    strncpy(temp, tupleString, BUFFER_SIZE);

    char* token;
    token = strtok(temp, ",");

    for (size_t i = 0; i < tupleSize && token != NULL; i++) {
        char* end;
        long numToken = strtol(token, &end, 10);
        
        if (numToken > INT_MAX || numToken < INT_MIN || *end != '\0') {
            exit(EXIT_FAILURE);
        }

        intTuple[i] = (int) numToken;
        token = strtok(NULL, ",");
    }
}

int main() {
    const char tupleString[] = "1,2,3,4,5";
    int intTuple[TUPLE_SIZE];

    convertTupleStringToIntTuple(tupleString, intTuple, TUPLE_SIZE);

    for (size_t i = 0; i < TUPLE_SIZE; i++) {
        printf("%d ", intTuple[i]);
    }

    return 0;
}