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

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->string = (char *)malloc(strlen(str) + 1);
    if (tuple->string == NULL) {
        free(tuple);
        return NULL;
    }
    strcpy(tuple->string, str);

    if (list_size > 0) {
        tuple->list = (int *)malloc(list_size * sizeof(int));
        if (tuple->list == NULL) {
            free(tuple->string);
            free(tuple);
            return NULL;
        }
        memcpy(tuple->list, list, list_size * sizeof(int));
    } else {
        tuple->list = NULL;
    }

    tuple->list_size = list_size;
    return tuple;
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

    Tuple *tuple = create_tuple(str, list, list_size);
    if (tuple == NULL) {
        return EXIT_FAILURE;
    }

    printf("String: %s\n", tuple->string);
    printf("List: ");
    for (size_t i = 0; i < tuple->list_size; i++) {
        printf("%d ", tuple->list[i]);
    }
    printf("\n");

    free_tuple(tuple);

    return EXIT_SUCCESS;
}