#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    char **strings;
    size_t count;
} StringTuple;

typedef struct {
    int *integers;
    size_t count;
} IntTuple;

IntTuple convertStringTupleToIntTuple(const StringTuple *strTuple) {
    IntTuple intTuple = {NULL, 0};

    if (strTuple == NULL || strTuple->count == 0 || strTuple->strings == NULL) {
        return intTuple;
    }

    intTuple.integers = (int *)malloc(strTuple->count * sizeof(int));
    if (intTuple.integers == NULL) {
        return intTuple;
    }

    for (size_t i = 0; i < strTuple->count; i++) {
        if (strTuple->strings[i] == NULL) {
            free(intTuple.integers);
            intTuple.integers = NULL;
            intTuple.count = 0;
            return intTuple;
        }

        char *endptr;
        errno = 0;
        long val = strtol(strTuple->strings[i], &endptr, 10);

        if (errno == ERANGE || val < INT_MIN || val > INT_MAX || endptr == strTuple->strings[i] || *endptr != '\0') {
            free(intTuple.integers);
            intTuple.integers = NULL;
            intTuple.count = 0;
            return intTuple;
        }

        intTuple.integers[i] = (int)val;
    }

    intTuple.count = strTuple->count;
    return intTuple;
}

int main() {
    char *strValues[] = {"42", "-17", "0", "123456"};
    StringTuple strTuple = {strValues, 4};

    IntTuple intTuple = convertStringTupleToIntTuple(&strTuple);

    if (intTuple.integers != NULL) {
        for (size_t i = 0; i < intTuple.count; i++) {
            printf("%d\n", intTuple.integers[i]);
        }
        free(intTuple.integers);
    } else {
        printf("Conversion failed.\n");
    }

    return 0;
}