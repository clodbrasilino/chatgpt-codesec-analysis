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

ListOfLists* create_list_of_lists(size_t count) {
    ListOfLists *lol = (ListOfLists*)malloc(sizeof(ListOfLists));
    lol->lists = (List**)malloc(count * sizeof(List*));
    lol->count = count;
    for (size_t i = 0; i < count; ++i) {
        lol->lists[i] = NULL;
    }
    return lol;
}

void free_list_of_lists(ListOfLists *lol) {
    if (lol) {
        for (size_t i = 0; i < lol->count; ++i) {
            if (lol->lists[i]) {
                free(lol->lists[i]->data);
                free(lol->lists[i]);
            }
        }
        free(lol->lists);
        free(lol);
    }
}

List* create_list(size_t size) {
    List *list = (List*)malloc(sizeof(List));
    list->data = (int*)malloc(size * sizeof(int));
    list->size = size;
    return list;
}

ListOfLists* zip_lists(const ListOfLists *a, const ListOfLists *b) {
    if (a->count != b->count) {
        return NULL;
    }

    ListOfLists *result = create_list_of_lists(a->count);
    for (size_t i = 0; i < a->count; ++i) {
        result->lists[i] = create_list(a->lists[i]->size + b->lists[i]->size);
        size_t j;
        for (j = 0; j < a->lists[i]->size; ++j) {
            result->lists[i]->data[j] = a->lists[i]->data[j];
        }
        for (j = 0; j < b->lists[i]->size; ++j) {
            result->lists[i]->data[a->lists[i]->size + j] = b->lists[i]->data[j];
        }
    }
    return result;
}

void print_list_of_lists(const ListOfLists *lol) {
    for (size_t i = 0; i < lol->count; ++i) {
        for (size_t j = 0; j < lol->lists[i]->size; ++j) {
            printf("%d ", lol->lists[i]->data[j]);
        }
        printf("\n");
    }
}

int main() {
    ListOfLists *a = create_list_of_lists(2);
    a->lists[0] = create_list(3);
    a->lists[0]->data[0] = 1;
    a->lists[0]->data[1] = 2;
    a->lists[0]->data[2] = 3;
    a->lists[1] = create_list(2);
    a->lists[1]->data[0] = 4;
    a->lists[1]->data[1] = 5;

    ListOfLists *b = create_list_of_lists(2);
    b->lists[0] = create_list(2);
    b->lists[0]->data[0] = 6;
    b->lists[0]->data[1] = 7;
    b->lists[1] = create_list(3);
    b->lists[1]->data[0] = 8;
    b->lists[1]->data[1] = 9;
    b->lists[1]->data[2] = 10;

    ListOfLists *zipped = zip_lists(a, b);
    if (zipped) {
        print_list_of_lists(zipped);
        free_list_of_lists(zipped);
    }

    free_list_of_lists(a);
    free_list_of_lists(b);

    return 0;
}