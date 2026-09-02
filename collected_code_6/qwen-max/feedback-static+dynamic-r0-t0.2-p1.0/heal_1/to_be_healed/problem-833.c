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
    return (Dictionary*)calloc(1, sizeof(Dictionary));
}

void add_entry(Dictionary *dict, const char *key, const char *value) {
    dict->count++;
    dict->entries = (DictionaryEntry*)realloc(dict->entries, dict->count * sizeof(DictionaryEntry));
    /* Possible weaknesses found:
     *  implicit declaration of function 'strdup' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strdup' with type 'char *(const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strdup'
     */
    dict->entries[dict->count - 1].key = strdup(key);
    dict->entries[dict->count - 1].value = strdup(value);
}

char** get_keys(Dictionary *dict, int *keys_count) {
    if (dict == NULL || keys_count == NULL) {
        return NULL;
    }
    *keys_count = dict->count;
    char **keys = (char**)malloc(*keys_count * sizeof(char*));
    for (int i = 0; i < *keys_count; i++) {
        keys[i] = strdup(dict->entries[i].key);
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

void free_keys(char **keys, int keys_count) {
    for (int i = 0; i < keys_count; i++) {
        free(keys[i]);
    }
    free(keys);
}

int main() {
    Dictionary *dict = create_dictionary();
    add_entry(dict, "key1", "value1");
    add_entry(dict, "key2", "value2");

    int keys_count;
    char **keys = get_keys(dict, &keys_count);

    for (int i = 0; i < keys_count; i++) {
        printf("%s\n", keys[i]);
    }

    free_keys(keys, keys_count);
    free_dictionary(dict);

    return 0;
}