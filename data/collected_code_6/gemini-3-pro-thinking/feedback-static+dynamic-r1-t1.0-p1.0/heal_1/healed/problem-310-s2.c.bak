#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    char *input_copy = malloc(strlen(input) + 1);
    if (!input_copy) {
        free(tuple);
        return NULL;
    }
    strcpy(input_copy, input);

    size_t count = 0;
    char *token = strtok(input_copy, delim);
    while (token) {
        count++;
        token = strtok(NULL, delim);
    }

    strcpy(input_copy, input);

    if (count > 0) {
        tuple->items = malloc(count * sizeof(char*));
        if (!tuple->items) {
            free(input_copy);
            free(tuple);
            return NULL;
        }
    } else {
        tuple->items = NULL;
    }

    tuple->count = count;
    
    if (count > 0) {
        token = strtok(input_copy, delim);
        for (size_t idx = 0; token != NULL; idx++) {
            tuple->items[idx] = malloc(strlen(token) + 1);
            if (!tuple->items[idx]) {
                for (size_t i = 0; i < idx; i++) {
                    free(tuple->items[i]);
                }
                free(tuple->items);
                free(input_copy);
                free(tuple);
                return NULL;
            }
            strcpy(tuple->items[idx], token);
            token = strtok(NULL, delim);
        }
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