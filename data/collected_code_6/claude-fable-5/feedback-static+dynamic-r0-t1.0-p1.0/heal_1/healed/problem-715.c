#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

typedef struct {
    long *items;
    size_t count;
} Tuple;

static int count_tokens(const char *str, size_t *count)
{
    size_t n = 0;
    const char *p = str;

    if (str == NULL || count == NULL) {
        return -1;
    }

    while (*p != '\0') {
        while (*p == ' ' || *p == ',' || *p == '\t') {
            p++;
        }
        if (*p == '\0') {
            break;
        }
        n++;
        while (*p != '\0' && *p != ' ' && *p != ',' && *p != '\t') {
            p++;
        }
    }

    *count = n;
    return 0;
}

static int string_to_tuple(const char *str, Tuple *result)
{
    size_t n = 0;
    size_t i = 0;
    const char *p = NULL;

    if (str == NULL || result == NULL) {
        return -1;
    }

    result->items = NULL;
    result->count = 0;

    if (count_tokens(str, &n) != 0) {
        return -1;
    }

    if (n == 0) {
        return 0;
    }

    if (n > SIZE_MAX / sizeof(long)) {
        return -1;
    }

    result->items = malloc(n * sizeof(long));
    if (result->items == NULL) {
        return -1;
    }

    p = str;
    while (*p != '\0' && i < n) {
        while (*p == ' ' || *p == ',' || *p == '\t') {
            p++;
        }
        if (*p == '\0') {
            break;
        }
        {
            long value;
            char *endptr = NULL;

            errno = 0;
            value = strtol(p, &endptr, 10);
            if (endptr == p) {
                free(result->items);
                result->items = NULL;
                return -1;
            }
            if (*endptr != '\0' && *endptr != ' ' &&
                *endptr != ',' && *endptr != '\t') {
                free(result->items);
                result->items = NULL;
                return -1;
            }
            if (errno == ERANGE &&
                (value == LONG_MAX || value == LONG_MIN)) {
                free(result->items);
                result->items = NULL;
                return -1;
            }
            result->items[i] = value;
            i++;
            p = endptr;
        }
    }

    result->count = i;
    return 0;
}

static void print_tuple(const Tuple *t)
{
    size_t i = 0;

    if (t == NULL) {
        return;
    }

    if (printf("(") < 0) {
        return;
    }
    for (i = 0; i < t->count; i++) {
        if (i > 0) {
            if (printf(", ") < 0) {
                return;
            }
        }
        if (printf("%ld", t->items[i]) < 0) {
            return;
        }
    }
    if (printf(")\n") < 0) {
        return;
    }
}

static void free_tuple(Tuple *t)
{
    if (t != NULL) {
        free(t->items);
        t->items = NULL;
        t->count = 0;
    }
}

int main(void)
{
    const char *input = "1, -2, 3, 4, 5";
    Tuple result;

    if (string_to_tuple(input, &result) != 0) {
        if (fprintf(stderr, "Failed to convert string to tuple\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    print_tuple(&result);
    free_tuple(&result);

    return EXIT_SUCCESS;
}