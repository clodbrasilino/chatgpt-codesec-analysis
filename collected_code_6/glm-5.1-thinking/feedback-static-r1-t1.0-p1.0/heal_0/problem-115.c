#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *keys;
    int *values;
    size_t size;
    size_t capacity;
} Dictionary;

int are_all_dicts_empty(Dictionary **list, size_t count) {
    if (list == NULL) {
        return count == 0;
    }
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL && list[i]->size > 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    const size_t list_size = 3;
    Dictionary **dict_list = malloc(list_size * sizeof(Dictionary *));
    if (dict_list == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list_size; i++) {
        dict_list[i] = malloc(sizeof(Dictionary));
        if (dict_list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dict_list[j]->keys);
                free(dict_list[j]->values);
                free(dict_list[j]);
            }
            free(dict_list);
            return EXIT_FAILURE;
        }
        dict_list[i]->keys = NULL;
        dict_list[i]->values = NULL;
        dict_list[i]->size = 0;
        dict_list[i]->capacity = 0;
    }

    int result = are_all_dicts_empty(dict_list, list_size);
    printf("%d\n", result);

    for (size_t i = 0; i < list_size; i++) {
        free(dict_list[i]->keys);
        free(dict_list[i]->values);
        free(dict_list[i]);
    }
    free(dict_list);

    return EXIT_SUCCESS;
}