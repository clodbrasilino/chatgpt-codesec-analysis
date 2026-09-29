#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

Tuple* create_tuple_from_string(const char *str, char delimiter);
void free_tuple(Tuple *tuple);

Tuple* create_tuple_from_string(const char *str, char delimiter) {
    if (!str) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    size_t delim_count = 0;
    for (const char *p = str; *p != '\0'; p++) {
        if (*p == delimiter) {
            delim_count++;
        }
    }

    tuple->count = delim_count + 1;
    tuple->elements = malloc(tuple->count * sizeof(char *));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }

    size_t index = 0;
    const char *start = str;
    const char *end = str;

    while (1) {
        if (*end == delimiter || *end == '\0') {
            size_t len = (size_t)(end - start);
            tuple->elements[index] = malloc(len + 1);
            if (!tuple->elements[index]) {
                for (size_t i = 0; i < index; i++) {
                    free(tuple->elements[i]);
                }
                free(tuple->elements);
                free(tuple);
                return NULL;
            }
            
            for (size_t i = 0; i < len; i++) {
                tuple->elements[index][i] = start[i];
            }
            tuple->elements[index][len] = '\0';
            
            index++;
            if (*end == '\0') {
                break;
            }
            start = end + 1;
        }
        end++;
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (!tuple) {
        return;
    }
    if (tuple->elements) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
    }
    free(tuple);
}

int main(void) {
    const char *input_string = "value1,value2,value3,value4";
    
    Tuple *parsed_tuple = create_tuple_from_string(input_string, ',');
    
    if (!parsed_tuple) {
        fprintf(stderr, "Failed to create tuple from string.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < parsed_tuple->count; i++) {
        printf("[%zu]: %s\n", i, parsed_tuple->elements[i]);
    }

    free_tuple(parsed_tuple);
    
    return EXIT_SUCCESS;
}