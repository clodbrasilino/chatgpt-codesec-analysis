#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TUPLE_SIZE 5
#define BUFFER_SIZE (TUPLE_SIZE * 2 + 1)

void convertTupleStringToIntTuple(const char* tupleString, int* intTuple, size_t tupleSize) {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char temp[BUFFER_SIZE];

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if (strlen(tupleString) >= BUFFER_SIZE) {
        exit(EXIT_FAILURE);
    }

    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
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