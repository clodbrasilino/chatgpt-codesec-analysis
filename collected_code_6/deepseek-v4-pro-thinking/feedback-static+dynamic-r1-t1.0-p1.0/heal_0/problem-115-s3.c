#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    size_t size;
} Dictionary;

typedef struct {
    Dictionary **items;
    size_t length;
} DictionaryList;

bool all_dictionaries_empty(const DictionaryList *list) {
    if (list == NULL) {
        return false;
    }
    if (list->length == 0) {
        return true;
    }
    if (list->items == NULL) {
        return false;
    }
    for (size_t i = 0; i < list->length; ++i) {
        if (list->items[i] == NULL || list->items[i]->size != 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    Dictionary d1 = {0};
    Dictionary d2 = {3};
    Dictionary *items_all_empty[] = { &d1, &d1 };
    DictionaryList list_all_empty = { items_all_empty, 2 };
    Dictionary *items_not_all[] = { &d1, &d2 };
    DictionaryList list_not_all = { items_not_all, 2 };
    DictionaryList list_empty = { NULL, 0 };

    printf("%d\n", all_dictionaries_empty(&list_all_empty));
    printf("%d\n", all_dictionaries_empty(&list_not_all));
    printf("%d\n", all_dictionaries_empty(&list_empty));

    return 0;
}