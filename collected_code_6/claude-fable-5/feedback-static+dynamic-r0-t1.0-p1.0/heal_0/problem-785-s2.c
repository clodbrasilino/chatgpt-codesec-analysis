#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

int parse_tuple(const char *input, long **result, size_t *count)
{
    const char *p;
    long *values;
    long *tmp;
    size_t capacity;
    size_t n;
    char *endptr;
    long val;

    if (input == NULL || result == NULL || count == NULL) {
        return -1;
    }

    *result = NULL;
    *count = 0;

    p = input;
    while (isspace((unsigned char)*p)) {
        p++;
    }

    if (*p != '(') {
        return -1;
    }
    p++;

    capacity = 4;
    values = malloc(capacity * sizeof(*values));
    if (values == NULL) {
        return -1;
    }

    n = 0;

    while (isspace((unsigned char)*p)) {
        p++;
    }

    if (*p == ')') {
        p++;
        while (isspace((unsigned char)*p)) {
            p++;
        }
        if (*p != '\0') {
            free(values);
            return -1;
        }
        *result = values;
        *count = 0;
        return 0;
    }

    for (;;) {
        while (isspace((unsigned char)*p)) {
            p++;
        }

        errno = 0;
        val = strtol(p, &endptr, 10);
        if (endptr == p || errno == ERANGE) {
            free(values);
            return -1;
        }
        p = endptr;

        if (n == capacity) {
            if (capacity > SIZE_MAX / (2 * sizeof(*values))) {
                free(values);
                return -1;
            }
            capacity *= 2;
            tmp = realloc(values, capacity * sizeof(*values));
            if (tmp == NULL) {
                free(values);
                return -1;
            }
            values = tmp;
        }
        values[n] = val;
        n++;

        while (isspace((unsigned char)*p)) {
            p++;
        }

        if (*p == ',') {
            p++;
            continue;
        }

        if (*p == ')') {
            p++;
            break;
        }

        free(values);
        return -1;
    }

    while (isspace((unsigned char)*p)) {
        p++;
    }

    if (*p != '\0') {
        free(values);
        return -1;
    }

    *result = values;
    *count = n;
    return 0;
}

int main(void)
{
    const char *tests[] = {
        "(1, 2, 3)",
        "( 10 , -20 , 30 )",
        "(42)",
        "()",
        "(1, 2,",
        "not a tuple"
    };
    size_t num_tests;
    size_t i;
    size_t j;
    long *values;
    size_t count;

    num_tests = sizeof(tests) / sizeof(tests[0]);

    for (i = 0; i < num_tests; i++) {
        values = NULL;
        count = 0;
        if (parse_tuple(tests[i], &values, &count) == 0) {
            printf("Input: %s -> Parsed %zu values: ", tests[i], count);
            for (j = 0; j < count; j++) {
                printf("%ld", values[j]);
                if (j + 1 < count) {
                    printf(", ");
                }
            }
            printf("\n");
            free(values);
        } else {
            printf("Input: %s -> Parse error\n", tests[i]);
        }
    }

    return 0;
}