#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} IntList;

typedef struct {
    IntList **lists;
    size_t count;
} ListOfLists;

ListOfLists* create_list_of_lists(size_t count) {
    ListOfLists *lol = (ListOfLists *)malloc(sizeof(ListOfLists));
    lol->count = count;
    lol->lists = (IntList **)malloc(count * sizeof(IntList *));
    for (size_t i = 0; i < count; ++i) {
        lol->lists[i] = NULL;
    }
    return lol;
}

IntList* create_int_list(int *data, size_t length) {
    IntList *list = (IntList *)malloc(sizeof(IntList));
    list->data = data;
    list->length = length;
    return list;
}

void add_list(ListOfLists *lol, IntList *list, size_t index) {
    if (index < lol->count) {
        lol->lists[index] = list;
    }
}

IntList* find_max_length_list(ListOfLists *lol) {
    if (!lol || lol->count == 0) {
        return NULL;
    }

    IntList *max_list = NULL;
    for (size_t i = 0; i < lol->count; ++i) {
        if (lol->lists[i] && (max_list == NULL || max_list->length < lol->lists[i]->length)) {
            max_list = lol->lists[i];
        }
    }
    return max_list;
}

void free_list(IntList *list) {
    free(list->data);
    free(list);
}

void free_list_of_lists(ListOfLists *lol) {
    for (size_t i = 0; i < lol->count; ++i) {
        if (lol->lists[i]) {
            free_list(lol->lists[i]);
        }
    }
    free(lol->lists);
    free(lol);
}

int main() {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5};
    int data3[] = {6, 7, 8, 9};

    ListOfLists *lol = create_list_of_lists(3);
    add_list(lol, create_int_list(data1, 3), 0);
    add_list(lol, create_int_list(data2, 2), 1);
    add_list(lol, create_int_list(data3, 4), 2);

    IntList *max_list = find_max_length_list(lol);
    if (max_list) {
        printf("Max length list: [");
        for (size_t i = 0; i < max_list->length; ++i) {
            printf("%d", max_list->data[i]);
            if (i < max_list->length - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    } else {
        printf("No lists found.\n");
    }

    free_list_of_lists(lol);
    return 0;
}