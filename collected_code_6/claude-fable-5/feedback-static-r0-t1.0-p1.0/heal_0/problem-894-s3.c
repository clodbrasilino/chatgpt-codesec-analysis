#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

typedef struct {
    double *values;
    size_t count;
} FloatTuple;

static int count_tokens(const char *str, size_t *count)
{
    size_t n = 0;
    const char *p = str;

    if (str == NULL || count == NULL) {
        return -1;
    }

    while (*p != '\0') {
        while (*p != '\0' && (isspace((unsigned char)*p) || *p == ',')) {
            p++;
        }
        if (*p != '\0') {
            n++;
            while (*p != '\0' && !isspace((unsigned char)*p) && *p != ',') {
                p++;
            }
        }
    }

    *count = n;
    return 0;
}

FloatTuple *string_to_tuple(const char *str)
{
    FloatTuple *tuple = NULL;
    size_t count = 0;
    size_t i = 0;
    const char *p = str;
    char *endptr = NULL;

    if (str == NULL) {
        return NULL;
    }

    if (count_tokens(str, &count) != 0 || count == 0) {
        return NULL;
    }

    tuple = malloc(sizeof(FloatTuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->values = malloc(count * sizeof(double));
    if (tuple->values == NULL) {
        free(tuple);
        return NULL;
    }
    tuple->count = count;

    for (i = 0; i < count; i++) {
        while (*p != '\0' && (isspace((unsigned char)*p) || *p == ',')) {
            p++;
        }
        errno = 0;
        tuple->values[i] = strtod(p, &endptr);
        if (endptr == p || errno == ERANGE) {
            free(tuple->values);
            free(tuple);
            return NULL;
        }
        p = endptr;
    }

    return tuple;
}

void free_tuple(FloatTuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->values);
        free(tuple);
    }
}

int main(void)
{
    const char *input = "1.5, 2.7, 3.9, 4.1";
    FloatTuple *tuple = NULL;
    size_t i = 0;

    tuple = string_to_tuple(input);
    if (tuple == NULL) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return EXIT_FAILURE;
    }

    printf("(");
    for (i = 0; i < tuple->count; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%g", tuple->values[i]);
    }
    printf(")\n");

    free_tuple(tuple);
    return EXIT_SUCCESS;
}