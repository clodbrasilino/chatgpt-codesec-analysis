#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    size_t count;
} IntTuple;

IntTuple* stringToIntTuple(const char *input) {
    IntTuple *tuple = (IntTuple*)malloc(sizeof(IntTuple));
    if (!tuple) return NULL;

    tuple->count = 0;
    tuple->values = NULL;

    const char *token;
    token = strtok((char *)input, " ,");

    while (token != NULL) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        int value = atoi(token);
        tuple->values = (int*)realloc(tuple->values, (tuple->count + 1) * sizeof(int));
        if (!tuple->values) {
            free(tuple);
            return NULL;
        }
        tuple->values[tuple->count++] = value;
        token = strtok(NULL, " ,");
    }

    return tuple;
}

void freeIntTuple(IntTuple *tuple) {
    free(tuple->values);
    free(tuple);
}

int main() {
    const char *input = "1, 2, 3, 4, 5";
    IntTuple *tuple = stringToIntTuple(input);

    if (tuple == NULL) {
        printf("Failed to create tuple\n");
        return 1;
    }

    for (size_t i = 0; i < tuple->count; ++i) {
        printf("%d ", tuple->values[i]);
    }
    printf("\n");

    freeIntTuple(tuple);
    return 0;
}