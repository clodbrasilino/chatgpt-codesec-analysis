#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'Dictionary::keys' is never used. [unusedStructMember]
     */
    int *keys;
    /* Possible weaknesses found:
     *  struct member 'Dictionary::values' is never used. [unusedStructMember]
     */
    int *values;
    size_t size;
    /* Possible weaknesses found:
     *  struct member 'Dictionary::capacity' is never used. [unusedStructMember]
     */
    size_t capacity;
} Dictionary;

typedef struct {
    Dictionary *dictionaries;
    size_t size;
} DictionaryList;

bool are_all_dictionaries_empty(const DictionaryList *list) {
    if (list == NULL) {
        return false;
    }

    for (size_t i = 0; i < list->size; i++) {
        if (list->dictionaries[i].size > 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    Dictionary empty_dicts[2] = {
        {NULL, NULL, 0, 0},
        {NULL, NULL, 0, 0}
    };

    Dictionary non_empty_dict = {NULL, NULL, 1, 1};

    DictionaryList list1 = {empty_dicts, 2};
    DictionaryList list2 = {&non_empty_dict, 1};
    DictionaryList list3 = {NULL, 0};

    if (are_all_dictionaries_empty(&list1)) {
        printf("List 1: All empty\n");
    } else {
        printf("List 1: Not all empty\n");
    }

    if (are_all_dictionaries_empty(&list2)) {
        printf("List 2: All empty\n");
    } else {
        printf("List 2: Not all empty\n");
    }

    if (are_all_dictionaries_empty(&list3)) {
        printf("List 3: All empty\n");
    } else {
        printf("List 3: Not all empty\n");
    }

    /* Possible weaknesses found:
     *  Condition 'are_all_dictionaries_empty(NULL)' is always false [knownConditionTrueFalse]
     *  Calling function 'are_all_dictionaries_empty' returns 0
     *  Condition 'are_all_dictionaries_empty(NULL)' is always false
     */
    if (are_all_dictionaries_empty(NULL)) {
        printf("NULL list: All empty\n");
    } else {
        printf("NULL list: Not all empty\n");
    }

    return 0;
}