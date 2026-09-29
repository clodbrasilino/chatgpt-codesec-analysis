#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'DictionaryEntry::key' is never used. [unusedStructMember]
     */
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int count;
} Dictionary;

int compare_strings(const void *a, const void *b) {
    return strcmp(*(char *const *)a, *(char *const *)b);
}

void extract_unique_values(Dictionary *dict, char ***unique_values, int *unique_count) {
    if (dict == NULL || dict->count == 0) {
        *unique_values = NULL;
        *unique_count = 0;
        return;
    }

    char **values = (char **)malloc(dict->count * sizeof(char *));
    if (values == NULL) {
        *unique_values = NULL;
        *unique_count = 0;
        return;
    }

    for (int i = 0; i < dict->count; ++i) {
        values[i] = dict->entries[i].value;
    }

    qsort(values, dict->count, sizeof(char *), (int (*)(const void *, const void *))compare_strings);

    *unique_count = 1;
    for (int i = 1; i < dict->count; ++i) {
        if (strcmp(values[i], values[*unique_count - 1]) != 0) {
            values[(*unique_count)++] = values[i];
        }
    }

    *unique_values = (char **)realloc(values, (*unique_count) * sizeof(char *));
    if (*unique_values == NULL) {
        *unique_count = 0;
    }
}

int main() {
    Dictionary dict = {
        .entries = (DictionaryEntry[]) {
            {"key1", "value1"},
            {"key2", "value2"},
            {"key3", "value1"},
            {"key4", "value3"},
            {"key5", "value2"}
        },
        .count = 5
    };

    char **unique_values;
    int unique_count;

    extract_unique_values(&dict, &unique_values, &unique_count);

    for (int i = 0; i < unique_count; ++i) {
        printf("%s\n", unique_values[i]);
    }

    free(unique_values);

    return 0;
}