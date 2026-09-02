#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    void *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int size;
    int capacity;
} Dictionary;

Dictionary *create_dictionary(int capacity) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) return NULL;
    dict->capacity = capacity;
    dict->size = 0;
    dict->entries = (DictionaryEntry *)calloc(capacity, sizeof(DictionaryEntry));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }
    return dict;
}

void destroy_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; ++i) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    free(dict);
}

void add_entry(Dictionary *dict, const char *key, void *value) {
    if (dict->size >= dict->capacity) {
        printf("Dictionary is full.\n");
        return;
    }
    int index = dict->size;
    dict->entries[index].key = strdup(key);
    dict->entries[index].value = value;
    dict->size++;
}

int find_entry(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->size; ++i) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

int is_key_in_dictionary(Dictionary *dict, const char *key) {
    return find_entry(dict, key) != -1;
}

int main() {
    Dictionary *dict = create_dictionary(3);
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary.\n");
        return 1;
    }

    add_entry(dict, "name", "Alice");
    add_entry(dict, "age", "25");
    add_entry(dict, "city", "New York");

    const char *test_key = "age";
    if (is_key_in_dictionary(dict, test_key)) {
        printf("Key '%s' found in the dictionary.\n", test_key);
    } else {
        printf("Key '%s' not found in the dictionary.\n", test_key);
    }

    destroy_dictionary(dict);
    return 0;
}