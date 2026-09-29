#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long first;
    long second;
} Tuple;

typedef enum {
    TUPLE_SUCCESS = 0,
    TUPLE_NULL_ERROR,
    TUPLE_PARSE_ERROR,
    TUPLE_RANGE_ERROR
} TupleError;

static const char *skip_ws(const char *s) {
    while (*s != '\0' && isspace((unsigned char)*s)) {
        s++;
    }
    return s;
}

TupleError string_to_tuple(const char *str, Tuple *out) {
    const char *p;
    char *end;
    long values[2];
    int i;

    if (str == NULL || out == NULL) {
        return TUPLE_NULL_ERROR;
    }

    p = str;

    for (i = 0; i < 2; i++) {
        p = skip_ws(p);
        if (*p == '\0') {
            return TUPLE_PARSE_ERROR;
        }

        errno = 0;
        values[i] = strtol(p, &end, 10);

        if (errno == ERANGE) {
            return TUPLE_RANGE_ERROR;
        }

        if (end == p) {
            return TUPLE_PARSE_ERROR;
        }

        p = skip_ws(end);

        if (i == 0) {
            if (*p != ',') {
                return TUPLE_PARSE_ERROR;
            }
            p++;
        }
    }

    if (*p != '\0') {
        return TUPLE_PARSE_ERROR;
    }

    out->first = values[0];
    out->second = values[1];

    return TUPLE_SUCCESS;
}

int main(void) {
    const char *input = " 42 , -17 ";
    Tuple tuple;
    TupleError result = string_to_tuple(input, &tuple);

    if (result != TUPLE_SUCCESS) {
        fprintf(stderr, "Failed to convert string to tuple: %d\n", result);
        return EXIT_FAILURE;
    }

    printf("%ld, %ld\n", tuple.first, tuple.second);

    return EXIT_SUCCESS;
}