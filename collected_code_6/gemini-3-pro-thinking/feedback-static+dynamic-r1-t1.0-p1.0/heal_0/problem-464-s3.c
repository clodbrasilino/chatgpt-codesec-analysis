#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    const char *key;
    int value;
} DictionaryEntry;

int check_all_values_same(const DictionaryEntry *dict, size_t size) {
    if (dict == NULL) {
        return -1; 
    }

    if (size <= 1) {
        return 1;
    }

    int first_value = dict[0].value;

    for (size_t i = 1; i < size; ++i) {
        if (dict[i].value != first_value) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    DictionaryEntry dict_same[] = {
        {"apple", 10},
        {"banana", 10},
        {"cherry", 10}
    };
    size_t size_same = sizeof(dict_same) / sizeof(dict_same[0]);

    DictionaryEntry dict_diff[] = {
        {"apple", 10},
        {"banana", 20},
        {"cherry", 10}
    };
    size_t size_diff = sizeof(dict_diff) / sizeof(dict_diff[0]);

    int result_same = check_all_values_same(dict_same, size_same);
    if (result_same != -1) {
        printf("dict_same: %d\n", result_same);
    }

    int result_diff = check_all_values_same(dict_diff, size_diff);
    if (result_diff != -1) {
        printf("dict_diff: %d\n", result_diff);
    }

    int result_null = check_all_values_same(NULL, 0);
    if (result_null == -1) {
        printf("dict_null: Error, invalid dictionary\n");
    }

    return 0;
}