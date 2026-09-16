#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t size;
    size_t capacity;
    const char **keys;
    int *values;
} Dict;

int dict_is_empty(const Dict *dict, int *is_empty) {
    if (is_empty == NULL) {
        return -1;
    }
    *is_empty = 1;
    if (dict != NULL) {
        *is_empty = (dict->size == 0);
    }
    return 0;
}

int main(void) {
    Dict *dict = calloc(1, sizeof(Dict));
    if (dict == NULL) {
        return EXIT_FAILURE;
    }

    int empty_flag = 0;
    int result = dict_is_empty(dict, &empty_flag);

    if (result == 0) {
        if (empty_flag) {
            printf("Dictionary is empty\n");
        } else {
            printf("Dictionary is not empty\n");
        }
    } else {
        printf("Error checking dictionary\n");
    }

    dict->capacity = 1;
    dict->keys = malloc(dict->capacity * sizeof(*dict->keys));
    dict->values = malloc(dict->capacity * sizeof(*dict->values));

    if (dict->keys != NULL && dict->values != NULL) {
        dict->size = 1;
        dict->keys[0] = "test";
        dict->values[0] = 1;
    } else {
        free(dict->keys);
        free(dict->values);
        dict->keys = NULL;
        dict->values = NULL;
        dict->capacity = 0;
    }

    result = dict_is_empty(dict, &empty_flag);

    if (result == 0) {
        if (empty_flag) {
            printf("Dictionary is empty\n");
        } else {
            printf("Dictionary is not empty\n");
        }
    } else {
        printf("Error checking dictionary\n");
    }

    result = dict_is_empty(NULL, &empty_flag);

    if (result == 0) {
        if (empty_flag) {
            printf("Correctly handled NULL dictionary input\n");
        }
    } else {
        printf("Error checking dictionary\n");
    }

    free(dict->keys);
    free(dict->values);
    free(dict);

    return EXIT_SUCCESS;
}