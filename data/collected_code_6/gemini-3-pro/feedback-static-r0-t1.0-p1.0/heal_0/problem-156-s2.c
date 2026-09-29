#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    if (!strTuple || !strTuple->strings || strTuple->count == 0) {
        return intTuple;
    }

    intTuple.integers = malloc(strTuple->count * sizeof(int));
    if (!intTuple.integers) {
        return intTuple;
    }

    for (size_t i = 0; i < strTuple->count; ++i) {
        if (!strTuple->strings[i]) {
            free(intTuple.integers);
            intTuple.integers = NULL;
            intTuple.count = 0;
            return intTuple;
        }

        char *endptr;
        errno = 0;
        long val = strtol(strTuple->strings[i], &endptr, 10);

        if (errno == ERANGE || val > INT_MAX || val < INT_MIN || endptr == strTuple->strings[i] || *endptr != '\0') {
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

int main(void) {
    char *strVals[] = {"10", "-25", "42", "0"};
    StringTuple strTuple = {strVals, 4};

    IntTuple intTuple = convertStringTupleToIntTuple(&strTuple);

    if (intTuple.integers) {
        for (size_t i = 0; i < intTuple.count; ++i) {
            printf("%d\n", intTuple.integers[i]);
        }
        free(intTuple.integers);
    } else {
        printf("Conversion failed.\n");
    }

    return 0;
}