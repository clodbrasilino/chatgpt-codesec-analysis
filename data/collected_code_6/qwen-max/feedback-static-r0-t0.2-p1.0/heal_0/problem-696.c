#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *data;
    size_t size;
} List;

typedef struct ListOfLists {
    List **lists;
    size_t count;
} ListOfLists;

List* create_list(size_t size) {
    List *list = (List *)malloc(sizeof(List));
    list->data = (int *)malloc(size * sizeof(int));
    list->size = size;
    return list;
}

ListOfLists* create_list_of_lists(size_t count, size_t size) {
    ListOfLists *lol = (ListOfLists *)malloc(sizeof(ListOfLists));
    lol->lists = (List **)malloc(count * sizeof(List *));
    for (size_t i = 0; i < count; ++i) {
        lol->lists[i] = create_list(size);
    }
    lol->count = count;
    return lol;
}

void free_list(List *list) {
    free(list->data);
    free(list);
}

void free_list_of_lists(ListOfLists *lol) {
    for (size_t i = 0; i < lol->count; ++i) {
        free_list(lol->lists[i]);
    }
    free(lol->lists);
    free(lol);
}

ListOfLists* zip_lists(const ListOfLists *a, const ListOfLists *b) {
    if (a->count != b->count || a->lists[0]->size != b->lists[0]->size) {
        return NULL;
    }

    ListOfLists *result = create_list_of_lists(a->count, a->lists[0]->size);

    for (size_t i = 0; i < a->count; ++i) {
        for (size_t j = 0; j < a->lists[i]->size; ++j) {
            result->lists[i]->data[j] = a->lists[i]->data[j];
            result->lists[i]->data[j + a->lists[i]->size] = b->lists[i]->data[j];
        }
    }

    return result;
}

int main() {
    ListOfLists *a = create_list_of_lists(2, 3);
    ListOfLists *b = create_list_of_lists(2, 3);

    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            a->lists[i]->data[j] = i * 3 + j;
            b->lists[i]->data[j] = (i + 2) * 3 + j;
        }
    }

    ListOfLists *zipped = zip_lists(a, b);

    if (zipped) {
        for (size_t i = 0; i < zipped->count; ++i) {
            for (size_t j = 0; j < zipped->lists[i]->size; ++j) {
                printf("%d ", zipped->lists[i]->data[j]);
            }
            printf("\n");
        }
        free_list_of_lists(zipped);
    }

    free_list_of_lists(a);
    free_list_of_lists(b);

    return 0;
}