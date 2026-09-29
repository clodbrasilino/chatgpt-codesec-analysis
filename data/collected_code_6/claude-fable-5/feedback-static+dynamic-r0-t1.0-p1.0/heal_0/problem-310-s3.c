#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

typedef struct {
    long *items;
    size_t count;
} Tuple;

static size_t count_elements(const char *str)
{
    size_t count = 1U;
    size_t i;

    for (i = 0U; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            count++;
        }
    }
    return count;
}

Tuple *string_to_tuple(const char *str)
{
    Tuple *tuple = NULL;
    char *copy = NULL;
    char *token = NULL;
    char *saveptr = NULL;
    char *endptr = NULL;
    size_t capacity;
    size_t index = 0U;
    long value;

    if ((str == NULL) || (str[0] == '\0')) {
        return NULL;
    }

    capacity = count_elements(str);

    tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = (long *)malloc(capacity * sizeof(long));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }
    tuple->count = 0U;

    copy = (char *)malloc(strlen(str) + 1U);
    if (copy == NULL) {
        free(tuple->items);
        free(tuple);
        return NULL;
    }
    memcpy(copy, str, strlen(str) + 1U);

    token = strtok_r(copy, ",", &saveptr);
    while (token != NULL) {
        while ((*token != '\0') && (isspace((unsigned char)*token) != 0)) {
            token++;
        }
        if (*token == '\0') {
            free(copy);
            free(tuple->items);
            free(tuple);
            return NULL;
        }

        errno = 0;
        value = strtol(token, &endptr, 10);
        if ((errno == ERANGE) || (endptr == token)) {
            free(copy);
            free(tuple->items);
            free(tuple);
            return NULL;
        }
        while ((*endptr != '\0') && (isspace((unsigned char)*endptr) != 0)) {
            endptr++;
        }
        if (*endptr != '\0') {
            free(copy);
            free(tuple->items);
            free(tuple);
            return NULL;
        }

        if (index >= capacity) {
            free(copy);
            free(tuple->items);
            free(tuple);
            return NULL;
        }

        tuple->items[index] = value;
        index++;
        token = strtok_r(NULL, ",", &saveptr);
    }

    free(copy);
    tuple->count = index;

    if (tuple->count == 0U) {
        free(tuple->items);
        free(tuple);
        return NULL;
    }

    return tuple;
}

void free_tuple(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->items);
        free(tuple);
    }
}

void print_tuple(const Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    (void)printf("(");
    for (i = 0U; i < tuple->count; i++) {
        (void)printf("%ld", tuple->items[i]);
        if (i < (tuple->count - 1U)) {
            (void)printf(", ");
        }
    }
    (void)printf(")\n");
}

int main(void)
{
    const char *input = "1, 2, 3, 40, 500";
    Tuple *tuple = string_to_tuple(input);

    if (tuple == NULL) {
        (void)fprintf(stderr, "Failed to convert string to tuple\n");
        return EXIT_FAILURE;
    }

    (void)printf("Input string: \"%s\"\n", input);
    (void)printf("Tuple: ");
    print_tuple(tuple);

    free_tuple(tuple);

    return EXIT_SUCCESS;
}