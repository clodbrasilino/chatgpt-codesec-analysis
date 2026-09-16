#include <stdio.h>
#include <stdlib.h>

#define DICT_SUCCESS 0
#define DICT_FAILURE -1

typedef struct {
    size_t size;
    size_t capacity;
    const char **keys;
    int *values;
} Dict;

int dict_is_empty(const Dict *dict, int *is_empty) {
    if (dict == NULL || is_empty == NULL) {
        return DICT_FAILURE;
    }
    *is_empty = (dict->size == 0);
    return DICT_SUCCESS;
}

int main(void) {
    Dict *dict = malloc(sizeof(Dict));
    if (dict == NULL) {
        return EXIT_FAILURE;
    }

    dict->size = 0;
    dict->capacity = 0;
    dict->keys = NULL;
    dict->values = NULL;

    int empty_flag = 0;
    int result = dict_is_empty(dict, &empty_flag);

    if (result == DICT_SUCCESS) {
        if (empty_flag) {
            printf("Dictionary is empty\n");
        } else {
            printf("Dictionary is not empty\n");
        }
    } else {
        printf("Error checking dictionary\n");
    }

    dict->keys = malloc(sizeof(const char *));
    dict->values = malloc(sizeof(int));

    if (dict->keys != NULL && dict->values != NULL) {
        dict->keys[0] = "test";
        dict->values[0] = 1;
        dict->size = 1;
        dict->capacity = 1;
    } else {
        free(dict->keys);
        free(dict->values);
        dict->keys = NULL;
        dict->values = NULL;
    }

    result = dict_is_empty(dict, &empty_flag);

    if (result == DICT_SUCCESS) {
        if (empty_flag) {
            printf("Dictionary is empty\n");
        } else {
            printf("Dictionary is not empty\n");
        }
    } else {
        printf("Error checking dictionary\n");
    }

    if (dict_is_empty(NULL, &empty_flag) == DICT_FAILURE) {
        printf("Correctly handled NULL dictionary input\n");
    }

    free(dict->keys);
    free(dict->values);
    free(dict);

    return EXIT_SUCCESS;
}