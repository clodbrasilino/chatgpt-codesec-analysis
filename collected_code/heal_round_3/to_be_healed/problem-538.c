#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **data;
    int size;
} Tuple;

Tuple convertStringListToTuple(char **stringList, int size) {
    Tuple tuple;
    tuple.data = (char **)calloc(size, sizeof(char *));
    tuple.size = size;
    if (tuple.data == NULL) {
        tuple.size = 0;
        return tuple;
    }
    
    for (int i = 0; i < size; i++) {
        if (stringList[i] != NULL) {
            /* Possible weaknesses found:
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             */
            size_t len = strlen(stringList[i]);
            tuple.data[i] = (char *)calloc(len + 1, sizeof(char));
            if (tuple.data[i] != NULL) {
                /* Possible weaknesses found:
                 *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
                 */
                strncpy(tuple.data[i], stringList[i], len);
                tuple.data[i][len] = '\0';
            }
        }
    }
    
    return tuple;
}

int main() {
    char *stringList[] = {"Hello", "World", "Example"};
    int size = sizeof(stringList) / sizeof(stringList[0]);
    Tuple tuple = convertStringListToTuple(stringList, size);
    
    for (int i = 0; i < tuple.size; i++) {
        if (tuple.data[i] != NULL) {
            printf("%d: %s\n", i, tuple.data[i]);
        }
    }
    for (int i = 0; i < tuple.size; i++) {
        free(tuple.data[i]);
    }
    free(tuple.data);
    
    return 0;
}