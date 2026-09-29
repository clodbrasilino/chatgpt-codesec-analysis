#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    const char *key;
    int value;
} DictItem;

int *extract_unique_values(const DictItem *dict, size_t dict_size, size_t *out_size);

int *extract_unique_values(const DictItem *dict, size_t dict_size, size_t *out_size) {
    if (!dict || !out_size) {
        return NULL;
    }

    if (dict_size == 0) {
        *out_size = 0;
        return NULL;
    }

    int *unique_values = malloc(dict_size * sizeof(int));
    if (!unique_values) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < dict_size; i++) {
        bool is_unique = true;
        for (size_t j = 0; j < count; j++) {
            if (unique_values[j] == dict[i].value) {
                is_unique = false;
                break;
            }
        }
        if (is_unique) {
            unique_values[count++] = dict[i].value;
        }
    }

    if (count == 0) {
        free(unique_values);
        *out_size = 0;
        return NULL;
    }

    if (count < dict_size) {
        int *resized = realloc(unique_values, count * sizeof(int));
        if (resized) {
            unique_values = resized;
        }
    }

    *out_size = count;
    return unique_values;
}

int main(void) {
    DictItem dict[] = {
        {"apple", 100},
        {"banana", 200},
        {"cherry", 100},
        {"date", 300},
        {"elderberry", 200},
        {"fig", 400}
    };
    
    size_t dict_size = sizeof(dict) / sizeof(dict[0]);
    size_t unique_count = 0;

    for (size_t i = 0; i < dict_size; i++) {
        printf("%s: %d\n", dict[i].key, dict[i].value);
    }

    int *unique_vals = extract_unique_values(dict, dict_size, &unique_count);

    if (unique_vals) {
        for (size_t i = 0; i < unique_count; i++) {
            printf("%d\n", unique_vals[i]);
        }
        free(unique_vals);
    } else if (unique_count > 0) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}