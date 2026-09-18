#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    const char *key;
    int value;
} DictEntry;

int* get_unique_values(const DictEntry *dict, size_t dict_size, size_t *out_unique_count) {
    if (dict == NULL || out_unique_count == NULL) {
        return NULL;
    }

    *out_unique_count = 0;

    if (dict_size == 0) {
        return NULL;
    }

    int *unique_vals = (int *)malloc(dict_size * sizeof(int));
    if (unique_vals == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < dict_size; ++i) {
        bool is_unique = true;
        for (size_t j = 0; j < count; ++j) {
            if (unique_vals[j] == dict[i].value) {
                is_unique = false;
                break;
            }
        }
        if (is_unique) {
            unique_vals[count] = dict[i].value;
            count++;
        }
    }

    int *resized_vals = (int *)realloc(unique_vals, count * sizeof(int));
    if (resized_vals == NULL) {
        free(unique_vals);
        return NULL;
    }

    *out_unique_count = count;
    return resized_vals;
}

int main(void) {
    DictEntry dictionary[] = {
        {"key1", 100},
        {"key2", 200},
        {"key3", 100},
        {"key4", 300},
        {"key5", 200}
    };

    size_t dict_size = sizeof(dictionary) / sizeof(dictionary[0]);
    size_t unique_count = 0;

    int *unique_values = get_unique_values(dictionary, dict_size, &unique_count);

    if (unique_values != NULL) {
        for (size_t i = 0; i < unique_count; ++i) {
            printf("%d\n", unique_values[i]);
        }
        free(unique_values);
    }

    return 0;
}