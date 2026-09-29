#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int count;
} Dictionary;

Dictionary* dictionary_create() {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->count = 0;
    dict->entries = NULL;
    return dict;
}

int dictionary_add(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    dict->entries = (DictionaryEntry*)realloc(dict->entries, (dict->count + 1) * sizeof(DictionaryEntry));
    if (dict->entries == NULL) {
        return -1;
    }
    dict->entries[dict->count].key = strdup(key);
    dict->entries[dict->count].value = strdup(value);
    if (dict->entries[dict->count].key == NULL || dict->entries[dict->count].value == NULL) {
        free(dict->entries[dict->count].key);
        free(dict->entries[dict->count].value);
        dict->entries = (DictionaryEntry*)realloc(dict->entries, dict->count * sizeof(DictionaryEntry));
        return -1;
    }
    dict->count++;
    return 0;
}

int dictionary_contains_key(Dictionary *dict, const char *key) {
    if (dict == NULL || key == NULL) {
        return 0;
    }
    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return 1;
        }
    }
    return 0;
}

void dictionary_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (int i = 0; i < dict->count; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    free(dict);
}

int main() {
    Dictionary *my_dict = dictionary_create();
    if (my_dict == NULL) {
        return EXIT_FAILURE;
    }

    dictionary_add(my_dict, "one", "1");
    dictionary_add(my_dict, "two", "2");
    dictionary_add(my_dict, "three", "3");

    if (dictionary_contains_key(my_dict, "two")) {
        printf("Key 'two' is present in the dictionary.\n");
    } else {
        printf("Key 'two' is not present in the dictionary.\n");
    }

    if (dictionary_contains_key(my_dict, "four")) {
        printf("Key 'four' is present in the dictionary.\n");
    } else {
        printf("Key 'four' is not present in the dictionary.\n");
    }

    dictionary_free(my_dict);
    return EXIT_SUCCESS;
}