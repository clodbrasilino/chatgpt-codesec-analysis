#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TUPLE_SIZE 5
#define BUFFER_SIZE (TUPLE_SIZE * 2 + 1)

void convertTupleStringToIntTuple(const char* tupleString, int* intTuple, size_t tupleSize) {
    if (tupleString == NULL || intTuple == NULL || tupleSize == 0 || tupleSize > TUPLE_SIZE) {
        exit(EXIT_FAILURE);
    }

    size_t inputLen = strnlen(tupleString, BUFFER_SIZE + 1);

    if (inputLen > BUFFER_SIZE) {
        exit(EXIT_FAILURE);
    }

    char* temp = calloc(BUFFER_SIZE, sizeof(char));

    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(temp, tupleString, inputLen);
    temp[inputLen] = '\0';

    char* token;
    token = strtok(temp, ",");

    for (size_t i = 0; token != NULL && i < tupleSize; i++) {
        char* end;
        long numToken = strtol(token, &end, 10);

        if (end == token || *end != '\0' || numToken > INT_MAX || numToken < INT_MIN) {
            free(temp);
            exit(EXIT_FAILURE);
        }

        intTuple[i] = (int) numToken;
        token = strtok(NULL, ",");
    }

    free(temp);
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