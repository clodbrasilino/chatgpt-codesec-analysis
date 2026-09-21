#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **elements;
    size_t size;
} Tuple;

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static char *safe_strdup(const char *str, size_t len) {
    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    size_t i;
    for (i = 0; i < len; i++) {
        copy[i] = str[i];
    }
    copy[len] = '\0';
    return copy;
}

Tuple string_to_tuple(const char *str) {
    Tuple tuple;
    tuple.elements = NULL;
    tuple.size = 0;

    if (str == NULL) {
        return tuple;
    }

    size_t len = safe_strlen(str, SIZE_MAX);
    
    if (len == 0) {
        return tuple;
    }

    char *copy = safe_strdup(str, len);
    if (copy == NULL) {
        return tuple;
    }

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

        size_t token_len = safe_strlen(token, SIZE_MAX);
        
        while (token_len > 0 && token[token_len - 1] == ' ') {
            token[token_len - 1] = '\0';
            token_len--;
        }

        if (token_len == 0) {
            token = strtok_r(NULL, ",", &saveptr);
            continue;
        }

        if (tuple.size == capacity) {
            size_t new_capacity = capacity * 2;
            if (new_capacity < capacity) {
                for (size_t i = 0; i < tuple.size; i++) {
                    free(tuple.elements[i]);
                }
                free(tuple.elements);
                free(copy);
                tuple.elements = NULL;
                tuple.size = 0;
                return tuple;
            }
            char **new_elements = realloc(tuple.elements, new_capacity * sizeof(char *));
            if (new_elements == NULL) {
                for (size_t i = 0; i < tuple.size; i++) {
                    free(tuple.elements[i]);
                }
                free(tuple.elements);
                free(copy);
                tuple.elements = NULL;
                tuple.size = 0;
                return tuple;
            }
            tuple.elements = new_elements;
            capacity = new_capacity;
        }

        char *element = safe_strdup(token, token_len);
        if (element == NULL) {
            for (size_t i = 0; i < tuple.size; i++) {
                free(tuple.elements[i]);
            }
            free(tuple.elements);
            free(copy);
            tuple.elements = NULL;
            tuple.size = 0;
            return tuple;
        }

        tuple.elements[tuple.size] = element;
        tuple.size++;

        token = strtok_r(NULL, ",", &saveptr);
    }

    free(copy);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->size; i++) {
        free(tuple->elements[i]);
    }
    free(tuple->elements);
    tuple->elements = NULL;
    tuple->size = 0;
}

int main(void) {
    const char *input = "apple, banana, cherry, date";
    Tuple result = string_to_tuple(input);

    if (result.elements == NULL) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return 1;
    }

    printf("Tuple elements (%zu):\n", result.size);
    for (size_t i = 0; i < result.size; i++) {
        printf("  [%zu] = '%s'\n", i, result.elements[i]);
    }

    free_tuple(&result);
    return 0;
}