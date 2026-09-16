#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dictionary {
    char **keys;
    int *values;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *create_dictionary(size_t initial_capacity) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->keys = (char **)calloc(initial_capacity, sizeof(char *));
    dict->values = (int *)calloc(initial_capacity, sizeof(int));
    if (!dict->keys || !dict->values) {
        free(dict);
        /* Possible weaknesses found:
         *  Dereferencing 'dict' after it is deallocated / released [deallocuse]
         */
        free(dict->keys);
        /* Possible weaknesses found:
         *  Dereferencing 'dict' after it is deallocated / released [deallocuse]
         */
        free(dict->values);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = initial_capacity;
    return dict;
}

void destroy_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->size; ++i) {
        free(dict->keys[i]);
    }
    free(dict->keys);
    free(dict->values);
    free(dict);
}

int insert_into_dictionary(Dictionary *dict, const char *key, int value) {
    if (dict->size == dict->capacity) {
        dict->capacity *= 2;
        dict->keys = (char **)realloc(dict->keys, dict->capacity * sizeof(char *));
        dict->values = (int *)realloc(dict->values, dict->capacity * sizeof(int));
        if (!dict->keys || !dict->values) return -1;
    }

    dict->keys[dict->size] = (char *)malloc((strlen(key) + 1) * sizeof(char));
    if (!dict->keys[dict->size]) return -2;
    strcpy(dict->keys[dict->size], key);
    dict->values[dict->size] = value;
    dict->size++;
    return 0;
}

int is_key_in_dictionary(Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->size; ++i) {
        if (strcmp(dict->keys[i], key) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    Dictionary *dict = create_dictionary(10);
    if (!dict) {
        printf("Failed to create dictionary\n");
        return 1;
    }

    insert_into_dictionary(dict, "apple", 5);
    insert_into_dictionary(dict, "banana", 7);
    insert_into_dictionary(dict, "cherry", 3);

    if (is_key_in_dictionary(dict, "apple")) {
        printf("Key 'apple' is present\n");
    } else {
        printf("Key 'apple' is not present\n");
    }

    if (is_key_in_dictionary(dict, "grape")) {
        printf("Key 'grape' is present\n");
    } else {
        printf("Key 'grape' is not present\n");
    }

    destroy_dictionary(dict);
    return 0;
}