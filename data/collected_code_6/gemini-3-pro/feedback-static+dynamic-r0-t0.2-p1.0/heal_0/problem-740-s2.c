#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair* items;
    size_t count;
} Dictionary;

Dictionary* tuple_to_dict(const char** tuple, size_t tuple_len) {
    if (tuple == NULL || tuple_len % 2 != 0) {
        return NULL;
    }

    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }

    dict->count = tuple_len / 2;
    dict->items = (KeyValuePair*)malloc(dict->count * sizeof(KeyValuePair));
    if (dict->items == NULL) {
        free(dict);
        return NULL;
    }

    for (size_t i = 0; i < dict->count; i++) {
        dict->items[i].key = strdup(tuple[i * 2]);
        if (dict->items[i].key == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dict->items[j].key);
                free(dict->items[j].value);
            }
            free(dict->items);
            free(dict);
            return NULL;
        }

        dict->items[i].value = strdup(tuple[i * 2 + 1]);
        if (dict->items[i].value == NULL) {
            free(dict->items[i].key);
            for (size_t j = 0; j < i; j++) {
                free(dict->items[j].key);
                free(dict->items[j].value);
            }
            free(dict->items);
            free(dict);
            return NULL;
        }
    }

    return dict;
}

void free_dictionary(Dictionary* dict) {
    if (dict != NULL) {
        if (dict->items != NULL) {
            for (size_t i = 0; i < dict->count; i++) {
                free(dict->items[i].key);
                free(dict->items[i].value);
            }
            free(dict->items);
        }
        free(dict);
    }
}

int main(void) {
    const char* tuple[] = {"name", "Alice", "age", "30", "city", "New York"};
    size_t tuple_len = sizeof(tuple) / sizeof(tuple[0]);

    Dictionary* dict = tuple_to_dict(tuple, tuple_len);
    if (dict != NULL) {
        for (size_t i = 0; i < dict->count; i++) {
            printf("%s: %s\n", dict->items[i].key, dict->items[i].value);
        }
        free_dictionary(dict);
    } else {
        fprintf(stderr, "Failed to create dictionary.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}