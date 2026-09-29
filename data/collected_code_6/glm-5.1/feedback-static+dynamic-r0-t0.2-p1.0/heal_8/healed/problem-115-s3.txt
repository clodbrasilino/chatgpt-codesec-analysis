#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *keys;
    int *values;
    size_t size;
    size_t capacity;
} Dictionary;

typedef struct {
    Dictionary *dictionaries;
    size_t size;
} DictionaryList;

bool are_all_dictionaries_empty(const DictionaryList *list) {
    if (list == NULL) {
        return true;
    }

    for (size_t i = 0; i < list->size; i++) {
        if (list->dictionaries[i].size > 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int keys1[] = {1};
    int values1[] = {10};

    Dictionary dict1 = {NULL, NULL, 0, 0};
    Dictionary dict2 = {NULL, NULL, 0, 0};
    Dictionary dict3 = {keys1, values1, 1, 1};

    DictionaryList list1 = {&dict1, 1};

    Dictionary array2[] = {dict1, dict2};
    DictionaryList list2 = {array2, 2};

    Dictionary array3[] = {dict1, dict3};
    DictionaryList list3 = {array3, 2};

    DictionaryList list4 = {NULL, 0};

    printf("%d\n", are_all_dictionaries_empty(&list1));
    printf("%d\n", are_all_dictionaries_empty(&list2));
    printf("%d\n", are_all_dictionaries_empty(&list3));
    printf("%d\n", are_all_dictionaries_empty(&list4));
    printf("%d\n", are_all_dictionaries_empty(NULL));

    return 0;
}