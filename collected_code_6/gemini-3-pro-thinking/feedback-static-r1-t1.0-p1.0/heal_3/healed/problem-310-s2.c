#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 65536

typedef struct {
    char **items;
    size_t count;
} Tuple;

Tuple* create_tuple_from_string(const char *input, const char *delim);
void free_tuple(Tuple *tuple);

Tuple* create_tuple_from_string(const char *input, const char *delim) {
    if (!input || !delim) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }
    tuple->items = NULL;
    tuple->count = 0;

    size_t input_len = strnlen(input, MAX_INPUT_LEN);
    char *input_copy = strndup(input, input_len);
    if (!input_copy) {
        free(tuple);
        return NULL;
    }

    size_t count = 0;
    char *saveptr1 = NULL;
    char *token = strtok_r(input_copy, delim, &saveptr1);
    while (token) {
        count++;
        token = strtok_r(NULL, delim, &saveptr1);
    }

    free(input_copy);

    tuple->count = count;

    if (count == 0) {
        tuple->items = NULL;
        return tuple;
    }

    tuple->items = malloc(count * sizeof(char*));
    if (!tuple->items) {
        free(tuple);
        return NULL;
    }

    input_copy = strndup(input, input_len);
    if (!input_copy) {
        free(tuple->items);
        free(tuple);
        return NULL;
    }

    size_t idx = 0;
    char *saveptr2 = NULL;
    token = strtok_r(input_copy, delim, &saveptr2);
    while (token && idx < count) {
        tuple->items[idx] = strdup(token);
        if (!tuple->items[idx]) {
            for (size_t i = 0; i < idx; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(input_copy);
            free(tuple);
            return NULL;
        }
        idx++;
        token = strtok_r(NULL, delim, &saveptr2);
    }

    free(input_copy);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (!tuple) {
        return;
    }
    if (tuple->items) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }
    free(tuple);
}

int main(void) {
    const char *my_string = "apple,banana,orange,grape";
    const char *delimiter = ",";
    
    Tuple *my_tuple = create_tuple_from_string(my_string, delimiter);
    
    if (my_tuple) {
        for (size_t i = 0; i < my_tuple->count; i++) {
            printf("Tuple[%zu]: %s\n", i, my_tuple->items[i]);
        }
        free_tuple(my_tuple);
    }
    
    return 0;
}