#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int dictionary_all_values_same(const Dictionary *dict) {
    if (dict == NULL || dict->entries == NULL || dict->size == 0) {
        return 1;
    }

    if (dict->size == 1) {
        return 1;
    }

    int first_value = dict->entries[0].value;

    for (size_t i = 1; i < dict->size; i++) {
        if (dict->entries[i].value != first_value) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    /* Possible weaknesses found:
     *  incompatible pointer to integer conversion initializing 'int' with an expression of type 'char[2]' [-Wint-conversion]
     *  (near initialization for '(anonymous)')
     *  initialization of 'int' from 'char *' makes integer from pointer without a cast [-Wint-conversion]
     *  excess elements in 'char[]' initializer
     *  (near initialization for 'entries1[0].value')
     */
    DictionaryEntry entries1[] = {(char[]){"a", 1}, (char[]){"b", 1}, (char[]){"c", 1}};
    Dictionary dict1 = {entries1, sizeof(entries1) / sizeof(entries1[0])};

    /* Possible weaknesses found:
     *  incompatible pointer to integer conversion initializing 'int' with an expression of type 'char[2]' [-Wint-conversion]
     *  (near initialization for '(anonymous)')
     *  initialization of 'int' from 'char *' makes integer from pointer without a cast [-Wint-conversion]
     *  excess elements in 'char[]' initializer
     *  (near initialization for 'entries2[0].value')
     */
    DictionaryEntry entries2[] = {(char[]){"a", 1}, (char[]){"b", 2}, (char[]){"c", 1}};
    Dictionary dict2 = {entries2, sizeof(entries2) / sizeof(entries2[0])};

    Dictionary dict3 = {NULL, 0};

    /* Possible weaknesses found:
     *  excess elements in 'char[]' initializer
     *  (near initialization for '(anonymous)')
     */
    DictionaryEntry entries4[] = {(char[]){"a", 5}};
    Dictionary dict4 = {entries4, sizeof(entries4) / sizeof(entries4[0])};

    printf("Dict1 all same: %d\n", dictionary_all_values_same(&dict1));
    printf("Dict2 all same: %d\n", dictionary_all_values_same(&dict2));
    printf("Dict3 all same: %d\n", dictionary_all_values_same(&dict3));
    printf("Dict4 all same: %d\n", dictionary_all_values_same(&dict4));

    return 0;
}