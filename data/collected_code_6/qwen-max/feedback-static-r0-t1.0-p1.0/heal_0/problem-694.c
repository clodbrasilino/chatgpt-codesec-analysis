#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *key;
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    int size;
} Dictionary;

bool is_value_unique(Dictionary *dict, int value) {
    for (int i = 0; i < dict->size; ++i) {
        if (dict->entries[i].value == value) {
            return false;
        }
    }
    return true;
}

void extract_unique_values(Dictionary *dict, int **unique_values, int *count) {
    *unique_values = malloc(dict->size * sizeof(int));
    if (*unique_values == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    *count = 0;
    for (int i = 0; i < dict->size; ++i) {
        if (is_value_unique(dict, dict->entries[i].value) && (*count < dict->size)) {
            (*unique_values)[*count] = dict->entries[i].value;
            (*count)++;
        }
    }
}

int main() {
    Dictionary dict = {
        .entries = (DictEntry[]) {
            {"one", 1},
            {"two", 2},
            {"three", 3},
            {"four", 4},
            {"duplicate", 2}
        },
        .size = 5
    };

    int *unique_values = NULL;
    int count = 0;

    extract_unique_values(&dict, &unique_values, &count);

    for (int i = 0; i < count; ++i) {
        printf("%d ", unique_values[i]);
    }

    free(unique_values);
    return 0;
}