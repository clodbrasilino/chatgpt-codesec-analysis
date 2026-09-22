#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t size;
} StringTuple;

StringTuple* convert_to_tuple(char **string_list, size_t list_size) {
    if (string_list == NULL) {
        return NULL;
    }

    StringTuple *tuple = (StringTuple*)malloc(sizeof(StringTuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->size = list_size;
    
    if (list_size == 0) {
        tuple->elements = NULL;
        return tuple;
    }

    tuple->elements = (char**)malloc(list_size * sizeof(char*));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < list_size; i++) {
        if (string_list[i] == NULL) {
            tuple->elements[i] = NULL;
        } else {
            size_t len = strlen(string_list[i]);
            tuple->elements[i] = (char*)malloc((len + 1) * sizeof(char));
            if (tuple->elements[i] == NULL) {
                for (size_t j = 0; j < i; j++) {
                    free(tuple->elements[j]);
                }
                free(tuple->elements);
                free(tuple);
                return NULL;
            }
            strcpy(tuple->elements[i], string_list[i]);
        }
    }

    return tuple;
}

void free_tuple(StringTuple *tuple) {
    if (tuple != NULL) {
        if (tuple->elements != NULL) {
            for (size_t i = 0; i < tuple->size; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
        }
        free(tuple);
    }
}

int main(void) {
    char *list[] = {"hello", "world", "tuple", "example"};
    size_t size = sizeof(list) / sizeof(list[0]);

    StringTuple *tuple = convert_to_tuple(list, size);
    
    if (tuple != NULL) {
        for (size_t i = 0; i < tuple->size; i++) {
            if (tuple->elements[i] != NULL) {
                printf("%s\n", tuple->elements[i]);
            }
        }
        free_tuple(tuple);
    }

    return 0;
}