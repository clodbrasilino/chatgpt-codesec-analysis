#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t size;
} Dictionary;

typedef struct {
    Dictionary *items;
    size_t count;
} DictionaryList;

int are_all_dictionaries_empty(const DictionaryList *list) {
    if (list == NULL) {
        return 1;
    }
    if (list->items == NULL) {
        return 1;
    }
    for (size_t i = 0; i < list->count; i++) {
        if (list->items[i].size > 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    DictionaryList list;
    list.count = 3;
    list.items = (Dictionary *)malloc(list.count * sizeof(Dictionary));
    if (list.items == NULL) {
        return EXIT_FAILURE;
    }

    list.items[0].size = 0;
    list.items[1].size = 0;
    list.items[2].size = 0;

    int result1 = are_all_dictionaries_empty(&list);
    printf("%d\n", result1);

    list.items[1].size = 5;

    int result2 = are_all_dictionaries_empty(&list);
    printf("%d\n", result2);

    free(list.items);
    list.items = NULL;
    list.count = 0;

    return EXIT_SUCCESS;
}