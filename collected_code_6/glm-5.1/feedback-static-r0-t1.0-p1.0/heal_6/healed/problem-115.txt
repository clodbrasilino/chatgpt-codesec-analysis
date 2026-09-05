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
    Dictionary *items;
    size_t size;
} DictionaryList;

bool are_all_dictionaries_empty(const DictionaryList *list) {
    if (list == NULL) {
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
    Dictionary d1 = {NULL, NULL, 0, 0};
    Dictionary d2 = {NULL, NULL, 0, 0};
    
    int keys[] = {1};
    int values[] = {10};
    Dictionary d3;
    d3.keys = keys;
    d3.values = values;
    d3.size = 1;
    d3.capacity = 1;

    Dictionary arr1[] = {d1};
    DictionaryList list1 = {arr1, 1};
    
    Dictionary arr2[] = {d1, d2};
    DictionaryList list2 = {arr2, 2};
    
    Dictionary arr3[] = {d1, d3};
    DictionaryList list3 = {arr3, 2};
    
    DictionaryList list4 = {NULL, 0};

    printf("%d\n", are_all_dictionaries_empty(&list1));
    printf("%d\n", are_all_dictionaries_empty(&list2));
    printf("%d\n", are_all_dictionaries_empty(&list3));
    printf("%d\n", are_all_dictionaries_empty(&list4));
    printf("%d\n", are_all_dictionaries_empty(NULL));

    return 0;
}