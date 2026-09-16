#include <stdio.h>
#include <stdbool.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'KeyValuePair::key' is never used. [unusedStructMember]
     */
    int key;
    /* Possible weaknesses found:
     *  struct member 'KeyValuePair::value' is never used. [unusedStructMember]
     */
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair* items;
    size_t size;
} Dictionary;

bool are_all_dictionaries_empty(const Dictionary* dict_list, size_t num_dicts) {
    if (dict_list == NULL && num_dicts > 0) {
        return false;
    }

    for (size_t i = 0; i < num_dicts; ++i) {
        if (dict_list[i].size > 0 || dict_list[i].items != NULL) {
            return false;
        }
    }

    return true;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'empty_dicts' can be declared as const array [constVariable]
     */
    Dictionary empty_dicts[3] = {
        {NULL, 0},
        {NULL, 0},
        {NULL, 0}
    };

    /* Possible weaknesses found:
     *  Variable 'mixed_dicts' can be declared as const array [constVariable]
     */
    Dictionary mixed_dicts[3] = {
        {NULL, 0},
        {(KeyValuePair[]){{1, 2}}, 1},
        {NULL, 0}
    };

    bool all_empty1 = are_all_dictionaries_empty(empty_dicts, 3);
    printf("%d\n", all_empty1);

    bool all_empty2 = are_all_dictionaries_empty(mixed_dicts, 3);
    printf("%d\n", all_empty2);

    return 0;
}