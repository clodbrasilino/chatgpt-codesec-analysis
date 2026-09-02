#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    int *values;
    int value_count;
} DictEntry;

typedef struct {
    DictEntry *entries;
    int entry_count;
} Dictionary;

int *extract_unique_values(Dictionary *dict, int *unique_count) {
    if (dict == NULL || unique_count == NULL) {
        return NULL;
    }

    int total_values = 0;
    for (int i = 0; i < dict->entry_count; i++) {
        total_values += dict->entries[i].value_count;
    }

    if (total_values == 0) {
        *unique_count = 0;
        return NULL;
    }

    int *all_values = (int *)malloc(total_values * sizeof(int));
    if (all_values == NULL) {
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < dict->entry_count; i++) {
        for (int j = 0; j < dict->entries[i].value_count; j++) {
            all_values[index++] = dict->entries[i].values[j];
        }
    }

    int *unique_values = (int *)malloc(total_values * sizeof(int));
    if (unique_values == NULL) {
        free(all_values);
        return NULL;
    }

    int unique_index = 0;
    for (int i = 0; i < total_values; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < unique_index; j++) {
            if (unique_values[j] == all_values[i]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            unique_values[unique_index++] = all_values[i];
        }
    }

    free(all_values);

    if (unique_index == 0) {
        free(unique_values);
        *unique_count = 0;
        return NULL;
    }

    int *result = (int *)realloc(unique_values, unique_index * sizeof(int));
    if (result == NULL) {
        free(unique_values);
        return NULL;
    }

    *unique_count = unique_index;
    return result;
}

int main(void) {
    int values1[] = {1, 2, 3, 2};
    int values2[] = {3, 4, 5};
    int values3[] = {6, 1, 7};

    DictEntry entries[3];
    entries[0].key = 1;
    entries[0].values = values1;
    entries[0].value_count = 4;

    entries[1].key = 2;
    entries[1].values = values2;
    entries[1].value_count = 3;

    entries[2].key = 3;
    entries[2].values = values3;
    entries[2].value_count = 3;

    Dictionary dict;
    dict.entries = entries;
    dict.entry_count = 3;

    int unique_count = 0;
    int *unique_values = extract_unique_values(&dict, &unique_count);

    if (unique_values != NULL) {
        for (int i = 0; i < unique_count; i++) {
            printf("%d ", unique_values[i]);
        }
        printf("\n");
        free(unique_values);
    } else {
        printf("No unique values found.\n");
    }

    return 0;
}