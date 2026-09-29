#include <stdio.h>
#include <stdlib.h>

struct DictionaryItem {
    /* Possible weaknesses found:
     *  struct member 'DictionaryItem::key' is never used. [unusedStructMember]
     */
    const char *key;
    int value;
};

int* extract_unique_values(const struct DictionaryItem *dictionary, size_t size, size_t *out_unique_count) {
    if (!dictionary || !out_unique_count) {
        return NULL;
    }

    if (size == 0) {
        *out_unique_count = 0;
        return NULL;
    }

    int *unique_values = (int *)malloc(size * sizeof(int));
    if (!unique_values) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        int current_value = dictionary[i].value;
        int is_duplicate = 0;

        for (size_t j = 0; j < count; ++j) {
            if (unique_values[j] == current_value) {
                is_duplicate = 1;
                break;
            }
        }

        if (!is_duplicate) {
            unique_values[count++] = current_value;
        }
    }

    if (count == 0) {
        free(unique_values);
        *out_unique_count = 0;
        return NULL;
    }

    int *resized_values = (int *)realloc(unique_values, count * sizeof(int));
    if (!resized_values) {
        *out_unique_count = count;
        return unique_values;
    }

    *out_unique_count = count;
    return resized_values;
}

int main(void) {
    struct DictionaryItem dict[] = {
        {"key1", 100},
        {"key2", 200},
        {"key3", 100},
        {"key4", 300},
        {"key5", 200}
    };
    
    size_t dict_size = sizeof(dict) / sizeof(dict[0]);
    size_t unique_count = 0;

    int *unique_vals = extract_unique_values(dict, dict_size, &unique_count);

    if (!unique_vals && unique_count > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < unique_count; ++i) {
        printf("%d\n", unique_vals[i]);
    }

    free(unique_vals);
    unique_vals = NULL;

    return EXIT_SUCCESS;
}