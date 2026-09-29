#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int *values;
    size_t num_values;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t num_entries;
} Dictionary;

int compare_ints(const void *a, const void *b) {
    int int_a = *((int *)a);
    int int_b = *((int *)b);

    if (int_a == int_b) return 0;
    else if (int_a < int_b) return -1;
    else return 1;
}

int sort_dictionary_list(Dictionary *dict, const char *key) {
    if (!dict || !key) {
        return -1;
    }

    for (size_t i = 0; i < dict->num_entries; ++i) {
        if (dict->entries[i].key != NULL && strcmp(dict->entries[i].key, key) == 0) {
            if (dict->entries[i].values != NULL && dict->entries[i].num_values > 0) {
                qsort(dict->entries[i].values, dict->entries[i].num_values, sizeof(int), compare_ints);
                return 0;
            }
        }
    }
    return -1;
}

int main(void) {
    Dictionary dict;
    dict.num_entries = 1;
    dict.entries = (DictionaryEntry *)malloc(dict.num_entries * sizeof(DictionaryEntry));
    if (!dict.entries) {
        return 1;
    }

    dict.entries[0].key = strdup("my_list");
    if (!dict.entries[0].key) {
        free(dict.entries);
        return 1;
    }

    dict.entries[0].num_values = 5;
    dict.entries[0].values = (int *)malloc(dict.entries[0].num_values * sizeof(int));
    if (!dict.entries[0].values) {
        free(dict.entries[0].key);
        free(dict.entries);
        return 1;
    }

    dict.entries[0].values[0] = 5;
    dict.entries[0].values[1] = 2;
    dict.entries[0].values[2] = 9;
    dict.entries[0].values[3] = 1;
    dict.entries[0].values[4] = 5;

    if (sort_dictionary_list(&dict, "my_list") == 0) {
        for (size_t i = 0; i < dict.entries[0].num_values; ++i) {
            printf("%d ", dict.entries[0].values[i]);
        }
        printf("\n");
    }

    free(dict.entries[0].values);
    free(dict.entries[0].key);
    free(dict.entries);

    return 0;
}