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
    tuple.size = size;

    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
         *  dereference of possibly-NULL 'tuple.data' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        tuple.data[i] = (char *)malloc((strlen(stringList[i]) + 1) * sizeof(char));
        /* Possible weaknesses found:
         *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
         */
        strcpy(tuple.data[i], stringList[i]);
    }

    return tuple;
}

int main() {
    char *stringList[] = {"Hello", "World", "Example"};
    int size = sizeof(stringList) / sizeof(stringList[0]);

    Tuple tuple = convertStringListToTuple(stringList, size);

    for (int i = 0; i < tuple.size; i++) {
        printf("%d: %s\n", i, tuple.data[i]);
    }

    for (int i = 0; i < tuple.size; i++) {
        free(tuple.data[i]);
    }
    free(tuple.data);

    return 0;
}