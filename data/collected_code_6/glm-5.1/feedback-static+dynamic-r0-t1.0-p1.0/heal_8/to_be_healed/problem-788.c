#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *string;
    int *list;
    size_t list_size;
} Tuple;

Tuple *create_tuple(const char *str, const int *list, size_t list_size) {
    if (str == NULL || (list == NULL && list_size > 0)) {
        return NULL;
    }

    Tuple *new_tuple = malloc(sizeof(Tuple));
    if (new_tuple == NULL) {
        return NULL;
    }

    new_tuple->string = strdup(str);
    if (new_tuple->string == NULL) {
        free(new_tuple);
        return NULL;
    }

    if (list_size > 0) {
        size_t buffer_size = list_size * sizeof(int);
        if (buffer_size / sizeof(int) != list_size) {
            free(new_tuple->string);
            free(new_tuple);
            return NULL;
        }
        new_tuple->list = malloc(buffer_size);
        if (new_tuple->list == NULL) {
            free(new_tuple->string);
            free(new_tuple);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_tuple->list, list, buffer_size);
    } else {
        new_tuple->list = NULL;
    }

    new_tuple->list_size = list_size;
    return new_tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->string);
        free(tuple->list);
        free(tuple);
    }
}

int main(void) {
    const char *str = "example";
    int list[] = {1, 2, 3, 4, 5};
    size_t list_size = sizeof(list) / sizeof(list[0]);

    Tuple *my_tuple = create_tuple(str, list, list_size);
    if (my_tuple != NULL) {
        printf("String: %s\n", my_tuple->string);
        printf("List: ");
        for (size_t i = 0; i < my_tuple->list_size; i++) {
            printf("%d ", my_tuple->list[i]);
        }
        printf("\n");
        free_tuple(my_tuple);
    } else {
        fprintf(stderr, "Failed to create tuple\n");
        return 1;
    }

    return 0;
}