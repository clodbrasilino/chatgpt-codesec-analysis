#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
} Dictionary;

Dictionary* create_dictionary(size_t initial_capacity) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    dict->entries = (DictionaryEntry *)malloc(initial_capacity * sizeof(DictionaryEntry));
    dict->count = 0;
    return dict;
}

void add_entry(Dictionary *dict, const char *key, int value) {
    if (dict->count >= 100) { // Assuming a max capacity of 100 for simplicity
        fprintf(stderr, "Dictionary is full\n");
        return;
    }
    dict->entries[dict->count].key = strdup(key);
    dict->entries[dict->count].value = value;
    dict->count += 1;
}

bool filter_by_value(const DictionaryEntry *entry, int threshold) {
    return entry->value > threshold;
}

Dictionary* filter_dictionary(const Dictionary *input_dict, int threshold) {
    Dictionary *filtered_dict = create_dictionary(input_dict->count);
    for (size_t i = 0; i < input_dict->count; ++i) {
        if (filter_by_value(&input_dict->entries[i], threshold)) {
            add_entry(filtered_dict, input_dict->entries[i].key, input_dict->entries[i].value);
        }
    }
    return filtered_dict;
}

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; ++i) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    free(dict);
}

int main() {
    Dictionary *dict = create_dictionary(5);
    add_entry(dict, "apple", 5);
    add_entry(dict, "banana", 3);
    add_entry(dict, "cherry", 7);

    Dictionary *filtered_dict = filter_dictionary(dict, 4);

    for (size_t i = 0; i < filtered_dict->count; ++i) {
        printf("%s: %d\n", filtered_dict->entries[i].key, filtered_dict->entries[i].value);
    }

    free_dictionary(dict);
    free_dictionary(filtered_dict);
    return 0;
}