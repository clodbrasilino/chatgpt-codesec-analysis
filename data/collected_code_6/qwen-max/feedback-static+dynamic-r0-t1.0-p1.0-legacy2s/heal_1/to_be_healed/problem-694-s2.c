#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    int size;
} Dictionary;

int compare(const void *a, const void *b) {
    return (*(DictEntry*)a).value - (*(DictEntry*)b).value;
}

int is_unique(const void *a, const void *b) {
    return (*(DictEntry*)a).value == (*(DictEntry*)b).value;
}

void extract_unique(Dictionary *dict, int **unique_values, int *unique_count) {
    qsort(dict->entries, dict->size, sizeof(DictEntry), compare);
    *unique_values = (int *)malloc(dict->size * sizeof(int));
    if (*unique_values == NULL) {
        exit(EXIT_FAILURE);
    }
    int prev_value = dict->entries[0].value;
    (*unique_values)[0] = prev_value;
    *unique_count = 1;
    for (int i = 1; i < dict->size; ++i) {
        if (dict->entries[i].value != prev_value) {
            prev_value = dict->entries[i].value;
            (*unique_values)[(*unique_count)++] = prev_value;
        }
    }
    *unique_values = (int *)realloc(*unique_values, *unique_count * sizeof(int));
    if (*unique_values == NULL) {
        exit(EXIT_FAILURE);
    }
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'values' can be declared as const array [constVariable]
     */
    int values[] = {3, 1, 2, 4, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'keys' can be declared as const array [constVariable]
     */
    int keys[] = {10, 20, 30, 40, 50, 60};
    Dictionary dict = {NULL, 0};

    dict.size = 6;
    dict.entries = (DictEntry *)malloc(dict.size * sizeof(DictEntry));
    if (dict.entries == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < dict.size; ++i) {
        dict.entries[i].key = keys[i];
        dict.entries[i].value = values[i];
    }

    int *unique_values;
    int unique_count;
    
    extract_unique(&dict, &unique_values, &unique_count);

    for (int i = 0; i < unique_count; ++i) {
        printf("%d ", unique_values[i]);
    }
    printf("\n");

    free(dict.entries);
    free(unique_values);

    return 0;
}