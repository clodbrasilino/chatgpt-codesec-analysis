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
    Dictionary *items;
    size_t size;
} DictionaryList;

bool are_all_dictionaries_empty(const DictionaryList *list) {
    if (list == NULL || list->items == NULL) {
        return true;
    }

    for (size_t i = 0; i < list->size; i++) {
        if (list->items[i].size > 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int keys1[] = {1};
    int values1[] = {10};
    int keys2[] = {2};
    int values2[] = {20};

    Dictionary empty_dict1 = {NULL, NULL, 0, 0};
    Dictionary empty_dict2 = {NULL, NULL, 0, 0};
    Dictionary non_empty_dict1 = {keys1, values1, 1, 1};
    /* Possible weaknesses found:
     *  Value stored to 'non_empty_dict2' during its initialization is never read [deadcode.DeadStores]
     *  Variable 'non_empty_dict2' is assigned a value that is never used. [unreadVariable]
     */
    Dictionary non_empty_dict2 = {keys2, values2, 1, 1};

    Dictionary empty_items[] = {empty_dict1, empty_dict2};
    DictionaryList empty_list = {empty_items, 2};

    Dictionary non_empty_items[] = {empty_dict1, non_empty_dict1};
    DictionaryList non_empty_list = {non_empty_items, 2};

    DictionaryList null_items_list = {NULL, 0};

    if (are_all_dictionaries_empty(&empty_list) == true) {
        printf("Empty list test passed.\n");
    } else {
        printf("Empty list test failed.\n");
    }

    if (are_all_dictionaries_empty(&non_empty_list) == false) {
        printf("Non-empty list test passed.\n");
    } else {
        printf("Non-empty list test failed.\n");
    }

    if (are_all_dictionaries_empty(NULL) == true) {
        printf("Null list test passed.\n");
    } else {
        printf("Null list test failed.\n");
    }

    if (are_all_dictionaries_empty(&null_items_list) == true) {
        printf("Null items list test passed.\n");
    } else {
        printf("Null items list test failed.\n");
    }

    return 0;
}