#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TUPLE_SIZE 5

void convertTupleStringToIntTuple(const char* tupleString, int* intTuple, size_t tupleSize) {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char temp[tupleSize * 2 + 1];
    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
     */
    strcpy(temp, tupleString);

    char* token;
    token = strtok(temp, ",");

    for (size_t i = 0; i < tupleSize && token != NULL; i++) {
        /* Possible weaknesses found:
         *   Unless checked, the resulting number can exceed the expected range  (CWE-190). If source untrusted, check both minimum and maximum, even if the  input had no minus sign (large numbers can roll over into negative number;  consider saving to an unsigned value if that is intended).
         */
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