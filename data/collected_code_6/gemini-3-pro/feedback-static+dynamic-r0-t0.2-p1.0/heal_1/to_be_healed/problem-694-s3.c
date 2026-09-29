#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'DictionaryEntry::key' is never used. [unusedStructMember]
     */
    char* key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry* entries;
    size_t size;
} Dictionary;

int* extract_unique_values(const Dictionary* dict, size_t* out_size) {
    if (!dict || !out_size) {
        return NULL;
    }

    int* unique_values = malloc(dict->size * sizeof(int));
    if (!unique_values) {
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < dict->size; ++i) {
        int current_value = dict->entries[i].value;
        int is_unique = 1;

        for (size_t j = 0; j < unique_count; ++j) {
            if (unique_values[j] == current_value) {
                is_unique = 0;
                break;
            }
        }

        if (is_unique) {
            unique_values[unique_count++] = current_value;
        }
    }

    int* resized_values = realloc(unique_values, unique_count * sizeof(int));
    if (!resized_values && unique_count > 0) {
        free(unique_values);
        return NULL;
    }

    *out_size = unique_count;
    return unique_count > 0 ? resized_values : NULL;
}

int main(void) {
    DictionaryEntry entries[] = {
        {"a", 10},
        {"b", 20},
        {"c", 10},
        {"d", 30},
        {"e", 20}
    };
    
    Dictionary dict = {entries, sizeof(entries) / sizeof(entries[0])};
    size_t unique_size = 0;
    
    int* unique_values = extract_unique_values(&dict, &unique_size);
    
    if (unique_values) {
        for (size_t i = 0; i < unique_size; ++i) {
            printf("%d\n", unique_values[i]);
        }
        free(unique_values);
    }
    
    return 0;
}