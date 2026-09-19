#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

void free_tuple(Tuple *tuple);
Tuple* string_to_tuple(const char *str);
void print_tuple(const Tuple *tuple);

void free_tuple(Tuple *tuple) {
    size_t i;
    if (!tuple) {
        return;
    }
    if (tuple->elements) {
        for (i = 0; i < tuple->count; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
    }
    free(tuple);
}

Tuple* string_to_tuple(const char *str) {
    Tuple *tuple;
    size_t len, i, j;

    if (!str) {
        return NULL;
    }

    tuple = malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    len = strlen(str);
    tuple->count = len;
    
    if (len == 0) {
        tuple->elements = NULL;
        return tuple;
    }

    tuple->elements = malloc(len * sizeof(char *));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }

    for (i = 0; i < len; i++) {
        tuple->elements[i] = malloc(2);
        if (!tuple->elements[i]) {
            for (j = 0; j < i; j++) {
                free(tuple->elements[j]);
            }
            free(tuple->elements);
            free(tuple);
            return NULL;
        }
        tuple->elements[i][0] = str[i];
        tuple->elements[i][1] = '\0';
    }

    return tuple;
}

void print_tuple(const Tuple *tuple) {
    size_t i;
    if (!tuple) {
        return;
    }
    printf("[");
    for (i = 0; i < tuple->count; i++) {
        printf("'%s'", tuple->elements[i]);
        if (i < tuple->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    fflush(stdout);
}

int main(int argc, char **argv) {
    int i;
    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            Tuple *tuple = string_to_tuple(argv[i]);
            if (tuple) {
                print_tuple(tuple);
                free_tuple(tuple);
            }
        }
    } else {
        char input[2048];
        while (scanf("%2047s", input) == 1) {
            Tuple *tuple = string_to_tuple(input);
            if (tuple) {
                print_tuple(tuple);
                free_tuple(tuple);
            }
        }
    }
    return EXIT_SUCCESS;
}