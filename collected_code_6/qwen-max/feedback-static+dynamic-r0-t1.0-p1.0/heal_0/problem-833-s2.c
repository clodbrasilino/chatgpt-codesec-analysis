#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int count;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->count = 0;
    dict->entries = NULL;
    return dict;
}

void add_entry(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL) return;
    dict->entries = (DictionaryEntry*)realloc(dict->entries, (dict->count + 1) * sizeof(DictionaryEntry));
    if (dict->entries == NULL) return;
    dict->entries[dict->count].key = strdup(key);
    dict->entries[dict->count].value = strdup(value);
    dict->count++;
}

char** get_keys(Dictionary *dict, int *keys_count) {
    if (dict == NULL || keys_count == NULL) return NULL;
    *keys_count = dict->count;
    char **keys = (char**)malloc((*keys_count) * sizeof(char*));
    if (keys == NULL) return NULL;
    for (int i = 0; i < *keys_count; i++) {
        keys[i] = dict->entries[i].key;
    }
    return keys;
}

void free_dictionary(Dictionary *dict) {
    if (dict != NULL) {
        for (int i = 0; i < dict->count; i++) {
            free(dict->entries[i].key);
            free(dict->entries[i].value);
        }
        free(dict->entries);
        free(dict);
    }
}

int main() {
    Dictionary *dict = create_dictionary();
    add_entry(dict, "key1", "value1");
    add_entry(dict, "key2", "value2");

    int keys_count;
    char **keys = get_keys(dict, &keys_count);

    for (int i = 0; i < keys_count; i++) {
        printf("%s\n", keys[i]);
        free(keys[i]); // Free each key as it was duplicated
    }

    free(keys); // Free the array of keys
    free_dictionary(dict);

    return 0;
}