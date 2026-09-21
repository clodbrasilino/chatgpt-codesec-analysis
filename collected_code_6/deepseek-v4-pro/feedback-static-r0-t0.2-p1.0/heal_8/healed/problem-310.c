#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

static size_t safe_strlen(const char *str, size_t maxlen) {
    size_t i = 0;
    while (i < maxlen && str[i] != '\0') {
        i++;
    }
    return i;
}

static char *safe_strndup(const char *str, size_t n) {
    char *dup = malloc(n + 1);
    if (dup == NULL) {
        return NULL;
    }
    size_t i;
    for (i = 0; i < n && str[i] != '\0'; i++) {
        dup[i] = str[i];
    }
    dup[i] = '\0';
    return dup;
}

Tuple string_to_tuple(const char *str) {
    Tuple tuple;
    tuple.elements = NULL;
    tuple.count = 0;

    if (str == NULL) {
        return tuple;
    }

    size_t len = 0;
    while (len < SIZE_MAX && str[len] != '\0') {
        len++;
    }
    if (len == SIZE_MAX) {
        return tuple;
    }

    if (len == 0) {
        return tuple;
    }

    if (len >= SIZE_MAX - 1) {
        return tuple;
    }

    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return tuple;
    }

    for (size_t i = 0; i < len; i++) {
        copy[i] = str[i];
    }
    copy[len] = '\0';

    size_t capacity = 4;
    tuple.elements = malloc(capacity * sizeof(char *));
    if (tuple.elements == NULL) {
        free(copy);
        return tuple;
    }

    char *saveptr;
    char *token = strtok_r(copy, ",", &saveptr);
    while (token != NULL) {
        while (*token == ' ') token++;
        if (*token == '\0') {
            token = strtok_r(NULL, ",", &saveptr);
            continue;
        }

        size_t token_len = 0;
        while (token[token_len] != '\0') {
            token_len++;
        }
        char *end = token + token_len - 1;
        while (end > token && *end == ' ') {
            end--;
        }
        *(end + 1) = '\0';
        token_len = (size_t)(end - token + 1);

        if (tuple.count == capacity) {
            if (capacity > SIZE_MAX / 2 / sizeof(char *)) {
                for (size_t i = 0; i < tuple.count; i++) {
                    free(tuple.elements[i]);
                }
                free(tuple.elements);
                free(copy);
                tuple.elements = NULL;
                tuple.count = 0;
                return tuple;
            }
            capacity *= 2;
            char **new_elements = realloc(tuple.elements, capacity * sizeof(char *));
            if (new_elements == NULL) {
                for (size_t i = 0; i < tuple.count; i++) {
                    free(tuple.elements[i]);
                }
                free(tuple.elements);
                free(copy);
                tuple.elements = NULL;
                tuple.count = 0;
                return tuple;
            }
            tuple.elements = new_elements;
        }

        tuple.elements[tuple.count] = malloc(token_len + 1);
        if (tuple.elements[tuple.count] == NULL) {
            for (size_t i = 0; i < tuple.count; i++) {
                free(tuple.elements[i]);
            }
            free(tuple.elements);
            free(copy);
            tuple.elements = NULL;
            tuple.count = 0;
            return tuple;
        }

        for (size_t i = 0; i < token_len; i++) {
            tuple.elements[tuple.count][i] = token[i];
        }
        tuple.elements[tuple.count][token_len] = '\0';
        tuple.count++;
        token = strtok_r(NULL, ",", &saveptr);
    }

    free(copy);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    if (tuple->elements != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
    }
    tuple->elements = NULL;
    tuple->count = 0;
}

int main(void) {
    const char *input = "apple, banana, cherry, date";
    Tuple result = string_to_tuple(input);

    if (result.elements == NULL && result.count == 0) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return EXIT_FAILURE;
    }

    printf("Tuple elements (%zu):\n", result.count);
    for (size_t i = 0; i < result.count; i++) {
        printf("  [%zu] = '%s'\n", i, result.elements[i]);
    }

    free_tuple(&result);
    return EXIT_SUCCESS;
}