#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* str;
    int* list;
    size_t list_size;
} Tuple;

Tuple* create_tuple(const char* str, const int* list, size_t list_size) {
    if (str == NULL || (list == NULL && list_size > 0)) {
        return NULL;
    }

    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->str = strdup(str);
    if (tuple->str == NULL) {
        free(tuple);
        return NULL;
    }

    tuple->list_size = list_size;
    if (list_size > 0) {
        tuple->list = (int*)malloc(list_size * sizeof(int));
        if (tuple->list == NULL) {
            free(tuple->str);
            free(tuple);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tuple->list, list, list_size * sizeof(int));
    } else {
        tuple->list = NULL;
    }

    return tuple;
}

void free_tuple(Tuple* tuple) {
    if (tuple != NULL) {
        free(tuple->str);
        free(tuple->list);
        free(tuple);
    }
}

int main(void) {
    const char* my_string = "Hello, Tuple!";
    int my_list[] = {1, 2, 3, 4, 5};
    size_t list_size = sizeof(my_list) / sizeof(my_list[0]);

    Tuple* my_tuple = create_tuple(my_string, my_list, list_size);
    if (my_tuple == NULL) {
        fprintf(stderr, "Failed to create tuple.\n");
        return EXIT_FAILURE;
    }

    printf("String: %s\n", my_tuple->str);
    printf("List: ");
    for (size_t i = 0; i < my_tuple->list_size; ++i) {
        printf("%d ", my_tuple->list[i]);
    }
    printf("\n");

    free_tuple(my_tuple);

    return EXIT_SUCCESS;
}