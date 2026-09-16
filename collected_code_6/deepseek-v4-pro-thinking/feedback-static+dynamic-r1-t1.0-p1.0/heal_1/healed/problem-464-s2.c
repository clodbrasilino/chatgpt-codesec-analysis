#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    int value;
} DictEntry;

bool all_values_same(const DictEntry *dict, size_t size) {
    if (size == 0) {
        return true;
    }
    if (dict == NULL) {
        return false;
    }
    int first_value = dict[0].value;
    for (size_t i = 1; i < size; ++i) {
        if (dict[i].value != first_value) {
            return false;
        }
    }
    return true;
}

int main(void) {
    const DictEntry dict1[] = {
        {10},
        {10},
        {10}
    };
    const DictEntry dict2[] = {
        {10},
        {20},
        {10}
    };

    printf("%d\n", all_values_same(dict1, 3));
    printf("%d\n", all_values_same(dict2, 3));
    printf("%d\n", all_values_same(NULL, 0));

    return 0;
}