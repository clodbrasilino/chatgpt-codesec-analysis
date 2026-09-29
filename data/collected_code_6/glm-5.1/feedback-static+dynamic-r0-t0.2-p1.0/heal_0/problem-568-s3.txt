#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int capacity;
    int size;
    char **keys;
    int *values;
} Dictionary;

Dictionary *create_empty_dictionary() {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->capacity = 8;
    dict->size = 0;
    dict->keys = (char **)calloc(dict->capacity, sizeof(char *));
    if (dict->keys == NULL) {
        free(dict);
        return NULL;
    }
    dict->values = (int *)calloc(dict->capacity, sizeof(int));
    if (dict->values == NULL) {
        free(dict->keys);
        free(dict);
        return NULL;
    }
    return dict;
}

Dictionary **create_list_of_empty_dictionaries(size_t count) {
    if (count == 0) {
        return NULL;
    }
    Dictionary **list = (Dictionary **)malloc(count * sizeof(Dictionary *));
    if (list == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < count; i++) {
        list[i] = create_empty_dictionary();
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(list[j]->keys);
                free(list[j]->values);
                free(list[j]);
            }
            free(list);
            return NULL;
        }
    }
    return list;
}

void free_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (int i = 0; i < dict->size; i++) {
        free(dict->keys[i]);
    }
    free(dict->keys);
    free(dict->values);
    free(dict);
}

void free_list_of_dictionaries(Dictionary **list, size_t count) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free_dictionary(list[i]);
    }
    free(list);
}

int main() {
    size_t count = 5;
    Dictionary **list = create_list_of_empty_dictionaries(count);
    if (list == NULL) {
        fprintf(stderr, "Failed to allocate list of dictionaries\n");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < count; i++) {
        printf("Dictionary %zu: size=%d, capacity=%d\n", i, list[i]->size, list[i]->capacity);
    }
    free_list_of_dictionaries(list, count);
    return EXIT_SUCCESS;
}