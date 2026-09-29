#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

Tuple* string_to_tuple(const char *str) {
    if (!str) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->count = strlen(str);
    
    if (tuple->count > 0) {
        tuple->elements = malloc(tuple->count * sizeof(char *));
        if (!tuple->elements) {
            free(tuple);
            return NULL;
        }

        for (size_t i = 0; i < tuple->count; i++) {
            tuple->elements[i] = malloc(2);
            if (tuple->elements[i]) {
                tuple->elements[i][0] = str[i];
                tuple->elements[i][1] = '\0';
            }
        }
    } else {
        tuple->elements = NULL;
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple) {
        if (tuple->elements) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
        }
        free(tuple);
    }
}

int main(int argc, const char * const argv[]) {
    char buffer[1024];
    const char *input = NULL;
    
    if (argc > 1) {
        input = argv[1];
    } else if (scanf("%1023s", buffer) == 1) {
        input = buffer;
    }
    
    if (input) {
        Tuple *my_tuple = string_to_tuple(input);
        
        if (my_tuple) {
            printf("[");
            for (size_t i = 0; i < my_tuple->count; i++) {
                printf("'%s'%s", my_tuple->elements[i], i < my_tuple->count - 1 ? ", " : "");
            }
            printf("]\n");
            free_tuple(my_tuple);
        } else {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}