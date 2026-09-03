#include <stdio.h>
#include <stddef.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'DictionaryEntry::key' is never used. [unusedStructMember]
     */
    char *key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t size;
} Dictionary;

int all_values_same(const Dictionary *dict) {
    if (dict == NULL) {
        return -1;
    }
    if (dict->size == 0) {
        return 1;
    }
    if (dict->entries == NULL) {
        return -1;
    }
    int first_value = dict->entries[0].value;
    for (size_t i = 1; i < dict->size; ++i) {
        if (dict->entries[i].value != first_value) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    DictionaryEntry entries1[] = {
        {"apple", 1},
        {"banana", 1},
        {"cherry", 1}
    };
    Dictionary dict1 = {entries1, sizeof(entries1) / sizeof(entries1[0])};
    printf("%d\n", all_values_same(&dict1));

    DictionaryEntry entries2[] = {
        {"apple", 1},
        {"banana", 2},
        {"cherry", 1}
    };
    Dictionary dict2 = {entries2, sizeof(entries2) / sizeof(entries2[0])};
    printf("%d\n", all_values_same(&dict2));

    Dictionary dict3 = {NULL, 0};
    printf("%d\n", all_values_same(&dict3));

    printf("%d\n", all_values_same(NULL));

    return 0;
}