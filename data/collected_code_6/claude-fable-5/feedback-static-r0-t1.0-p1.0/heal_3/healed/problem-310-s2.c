#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

typedef struct {
    long *items;
    size_t count;
} Tuple;

static Tuple *tuple_create(size_t capacity)
{
    if (capacity == 0 || capacity > SIZE_MAX / sizeof(long)) {
        return NULL;
    }

    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    t->items = malloc(capacity * sizeof(long));
    if (t->items == NULL) {
        free(t);
        return NULL;
    }

    t->count = 0;
    return t;
}

static void tuple_destroy(Tuple *t)
{
    if (t != NULL) {
        free(t->items);
        free(t);
    }
}

static Tuple *string_to_tuple(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, MAX_INPUT_LEN);
    if (len == 0 || len >= MAX_INPUT_LEN) {
        return NULL;
    }

    size_t capacity = 1;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ',') {
            capacity++;
        }
    }

    Tuple *t = tuple_create(capacity);
    if (t == NULL) {
        return NULL;
    }

    if (len > SIZE_MAX - 1) {
        tuple_destroy(t);
        return NULL;
    }

    size_t copy_size = len + 1;
    char *copy = malloc(copy_size);
    if (copy == NULL) {
        tuple_destroy(t);
        return NULL;
    }

    memcpy(copy, str, len);
    copy[len] = '\0';

    char *saveptr = NULL;
    char *token = strtok_r(copy, ",", &saveptr);
    while (token != NULL) {
        while (isspace((unsigned char)*token)) {
            token++;
        }
        if (*token == '\0') {
            free(copy);
            tuple_destroy(t);
            return NULL;
        }

        errno = 0;
        char *endptr = NULL;
        long value = strtol(token, &endptr, 10);
        if (errno == ERANGE || endptr == token) {
            free(copy);
            tuple_destroy(t);
            return NULL;
        }
        while (isspace((unsigned char)*endptr)) {
            endptr++;
        }
        if (*endptr != '\0') {
            free(copy);
            tuple_destroy(t);
            return NULL;
        }

        if (t->count >= capacity) {
            free(copy);
            tuple_destroy(t);
            return NULL;
        }
        t->items[t->count] = value;
        t->count++;

        token = strtok_r(NULL, ",", &saveptr);
    }

    free(copy);

    if (t->count == 0) {
        tuple_destroy(t);
        return NULL;
    }

    return t;
}

static void tuple_print(const Tuple *t)
{
    if (t == NULL) {
        printf("(invalid)\n");
        return;
    }
    printf("(");
    for (size_t i = 0; i < t->count; i++) {
        printf("%ld", t->items[i]);
        if (i + 1 < t->count) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    const char *input = "1, 5, 7, 10, 13";

    Tuple *t = string_to_tuple(input);
    if (t == NULL) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return EXIT_FAILURE;
    }

    printf("Input string: \"%s\"\n", input);
    printf("Tuple: ");
    tuple_print(t);

    tuple_destroy(t);

    return EXIT_SUCCESS;
}