#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096U

typedef struct {
    long *items;
    size_t count;
} Tuple;

static int count_tokens(const char *str, size_t maxlen, size_t *count)
{
    size_t n = 0;
    size_t i = 0;

    if (str == NULL || count == NULL) {
        return -1;
    }

    while (i < maxlen && str[i] != '\0') {
        while (i < maxlen && (str[i] == ' ' || str[i] == ',' || str[i] == '\t')) {
            i++;
        }
        if (i >= maxlen || str[i] == '\0') {
            break;
        }
        n++;
        while (i < maxlen && str[i] != '\0' && str[i] != ' ' && str[i] != ',' && str[i] != '\t') {
            i++;
        }
    }

    *count = n;
    return 0;
}

static int string_to_tuple(const char *str, Tuple *result)
{
    size_t n = 0;
    size_t i = 0;
    size_t j = 0;
    size_t len = 0;
    size_t copy_size = 0;
    char *copy = NULL;
    char *token = NULL;
    char *saveptr = NULL;

    if (str == NULL || result == NULL) {
        return -1;
    }

    result->items = NULL;
    result->count = 0;

    len = strnlen(str, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return -1;
    }

    if (count_tokens(str, len, &n) != 0) {
        return -1;
    }

    if (n == 0) {
        return 0;
    }

    if (n > SIZE_MAX / sizeof(long)) {
        return -1;
    }

    if (len > SIZE_MAX - 1U) {
        return -1;
    }

    copy_size = len + 1U;
    copy = malloc(copy_size);
    if (copy == NULL) {
        return -1;
    }

    for (j = 0; j < len; j++) {
        copy[j] = str[j];
    }
    copy[len] = '\0';

    result->items = malloc(n * sizeof(long));
    if (result->items == NULL) {
        free(copy);
        return -1;
    }

    token = strtok_r(copy, " ,\t", &saveptr);
    while (token != NULL && i < n) {
        char *endptr = NULL;
        long value;

        errno = 0;
        value = strtol(token, &endptr, 10);
        if (endptr == token || *endptr != '\0') {
            free(copy);
            free(result->items);
            result->items = NULL;
            return -1;
        }
        if (errno == ERANGE && (value == LONG_MAX || value == LONG_MIN)) {
            free(copy);
            free(result->items);
            result->items = NULL;
            return -1;
        }
        result->items[i] = value;
        i++;
        token = strtok_r(NULL, " ,\t", &saveptr);
    }

    result->count = i;
    free(copy);
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