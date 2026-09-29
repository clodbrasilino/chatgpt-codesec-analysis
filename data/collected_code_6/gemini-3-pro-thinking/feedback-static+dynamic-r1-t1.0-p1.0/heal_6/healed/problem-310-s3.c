#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

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

Tuple* string_to_tuple(const char *str) {
    if (!str) {
        return NULL;
    }

    size_t len = strlen(str);
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (!tuple) {
        return NULL;
    }

    tuple->count = len;

    if (len == 0) {
        tuple->elements = NULL;
        return tuple;
    }

    tuple->elements = (char **)malloc(len * sizeof(char *));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        tuple->elements[i] = (char *)malloc(2);
        if (!tuple->elements[i]) {
            tuple->count = i;
            free_tuple(tuple);
            return NULL;
        }
        tuple->elements[i][0] = str[i];
        tuple->elements[i][1] = '\0';
    }

    return tuple;
}

void print_tuple(const Tuple *tuple) {
    if (!tuple) {
        return;
    }
    printf("[");
    for (size_t i = 0; i < tuple->count; i++) {
        printf("'%s'", tuple->elements[i]);
        if (i < tuple->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    fflush(stdout);
}

int main(int argc, char *argv[]) {
    char buffer[8192];
    buffer[0] = '\0';

    if (argc > 1) {
        strncpy(buffer, argv[1], sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';
    } else {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            return EXIT_SUCCESS;
        }
        buffer[strcspn(buffer, "\r\n")] = '\0';
    }

    Tuple *tuple = string_to_tuple(buffer);
    if (tuple) {
        print_tuple(tuple);
        free_tuple(tuple);
    }

    return EXIT_SUCCESS;
}