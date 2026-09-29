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

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->elements = NULL;
    tuple->count = len;

    if (len > 0) {
        tuple->elements = malloc(len * sizeof(char *));
        if (!tuple->elements) {
            free(tuple);
            return NULL;
        }
        for (size_t i = 0; i < len; i++) {
            tuple->elements[i] = malloc(2);
            if (tuple->elements[i]) {
                tuple->elements[i][0] = str[i];
                tuple->elements[i][1] = '\0';
            }
        }
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
        free(tuple);
    }
}

int main(void) {
    char buffer[2048];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0';

        Tuple *my_tuple = string_to_tuple(buffer);

        if (my_tuple) {
            printf("[");
            for (size_t i = 0; i < my_tuple->count; i++) {
                printf("'%s'", my_tuple->elements[i]);
                if (i < my_tuple->count - 1) {
                    printf(", ");
                }
            }
            printf("]\n");
            free_tuple(my_tuple);
        } else {
            return EXIT_FAILURE;
        }
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}