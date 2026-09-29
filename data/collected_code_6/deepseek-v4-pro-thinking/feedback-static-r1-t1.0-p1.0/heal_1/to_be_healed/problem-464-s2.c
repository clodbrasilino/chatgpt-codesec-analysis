#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'DictEntry::key' is never used. [unusedStructMember]
     */
    const char *key;
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
    /* Possible weaknesses found:
     *  Variable 'dict1' can be declared as const array [constVariable]
     */
    DictEntry dict1[] = {
        {"a", 10},
        {"b", 10},
        {"c", 10}
    };
    /* Possible weaknesses found:
     *  Variable 'dict2' can be declared as const array [constVariable]
     */
    DictEntry dict2[] = {
        {"a", 10},
        {"b", 20},
        {"c", 10}
    };

    printf("%d\n", all_values_same(dict1, 3));
    printf("%d\n", all_values_same(dict2, 3));
    printf("%d\n", all_values_same(NULL, 0));

    return 0;
}