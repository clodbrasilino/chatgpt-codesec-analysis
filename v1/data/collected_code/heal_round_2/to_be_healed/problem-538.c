#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **data;
    int size;
} Tuple;

Tuple convertStringListToTuple(char **stringList, int size) {
    Tuple tuple;
    tuple.data = (char **)malloc(size * sizeof(char *));
    if (tuple.data == NULL) {
        return tuple;
    }
    tuple.size = size;
    for (int i = 0; i < size; i++) {
        if (stringList[i] != NULL) {
            /* Possible weaknesses found:
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
             */
            tuple.data[i] = (char *)malloc((strlen(stringList[i]) + 1) * sizeof(char));
            if (tuple.data[i] != NULL) {
                /* Possible weaknesses found:
                 *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
                 *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
                 */
                strncpy(tuple.data[i], stringList[i], strlen(stringList[i]) + 1);
            }
        }
    }
    return tuple;
}

int main() {
    char *stringList[] = {"Hello", "World", "Example"};
    int size = sizeof(stringList) / sizeof(stringList[0]);
    Tuple tuple = convertStringListToTuple(stringList, size);

    /* Possible weaknesses found:
     *  use of uninitialized value 'tuple.size' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    for (int i = 0; i < tuple.size; i++) {
        if (tuple.data[i] != NULL) {
            printf("%d: %s\n", i, tuple.data[i]);
        }
    }
    for (int i = 0; i < tuple.size; i++) {
        if (tuple.data[i] != NULL) {
            free(tuple.data[i]);
        }
    }
    free(tuple.data);
    return 0;
}