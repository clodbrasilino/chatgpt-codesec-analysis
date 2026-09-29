#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int count;
} Dictionary;

int compare_strings(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

void extract_unique_values(Dictionary *dict, char ***unique_values, int *unique_count) {
    if (dict == NULL || dict->entries == NULL || dict->count <= 0) {
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

    qsort(values, dict->count, sizeof(char *), compare_strings);

    *unique_count = 1;
    for (int i = 1; i < dict->count; ++i) {
        if (strcmp(values[i], values[i - 1]) != 0) {
            (*unique_count)++;
        }
    }

    *unique_values = (char **)malloc(*unique_count * sizeof(char *));
    if (*unique_values == NULL) {
        free(values);
        *unique_count = 0;
        return;
    }

    int index = 0;
    (*unique_values)[index++] = values[0];
    for (int i = 1; i < dict->count; ++i) {
        if (strcmp(values[i], values[i - 1]) != 0) {
            (*unique_values)[index++] = values[i];
        }
    }

    free(values);
}

int main() {
    Dictionary dict = {
        .entries = (DictionaryEntry[]) {
            {"value1"},
            {"value2"},
            {"value1"},
            {"value3"},
            {"value2"}
        },
        .count = 5
    };

    char **unique_values;
    int unique_count;

    extract_unique_values(&dict, &unique_values, &unique_count);

    for (int i = 0; i < unique_count; ++i) {
        printf("%s\n", unique_values[i]);
    }

    for (int i = 0; i < unique_count; ++i) {
        free(unique_values[i]);
    }
    free(unique_values);

    return 0;
}