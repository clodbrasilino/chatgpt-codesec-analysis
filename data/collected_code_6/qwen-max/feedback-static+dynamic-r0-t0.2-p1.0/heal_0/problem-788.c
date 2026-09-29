#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int *list;
    size_t list_size;
} Tuple;

Tuple* create_tuple(const char *input_str, const int *input_list, size_t list_size) {
    if (input_str == NULL || input_list == NULL) return NULL;

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) return NULL;

    tuple->str = strdup(input_str);
    if (tuple->str == NULL) {
        free(tuple);
        return NULL;
    }

    tuple->list = (int *)malloc(list_size * sizeof(int));
    if (tuple->list == NULL) {
        free(tuple->str);
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < list_size; ++i) {
        tuple->list[i] = input_list[i];
    }
    tuple->list_size = list_size;

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->str);
        free(tuple->list);
        free(tuple);
    }
}

int main() {
    const char *test_str = "example";
    int test_list[] = {1, 2, 3};
    size_t list_size = sizeof(test_list) / sizeof(test_list[0]);

    Tuple *new_tuple = create_tuple(test_str, test_list, list_size);
    if (new_tuple != NULL) {
        printf("Tuple created: %s, [", new_tuple->str);
        for (size_t i = 0; i < new_tuple->list_size; ++i) {
            printf("%d", new_tuple->list[i]);
            if (i < new_tuple->list_size - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(new_tuple);
    } else {
        printf("Failed to create tuple.\n");
    }

    return 0;
}