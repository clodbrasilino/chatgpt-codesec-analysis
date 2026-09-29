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
    ListOfLists *lol = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (!lol) return NULL;
    lol->lists = (List **)calloc(count, sizeof(List *));
    if (!lol->lists) {
        free(lol);
        return NULL;
    }
    lol->count = count;
    return lol;
}

void free_list(List *list) {
    if (list) {
        free(list->data);
        free(list);
    }
}

void free_list_of_lists(ListOfLists *lol) {
    if (lol) {
        for (size_t i = 0; i < lol->count; ++i) {
            free_list(lol->lists[i]);
        }
        free(lol->lists);
        free(lol);
    }
}

List* create_list(size_t size) {
    List *list = (List *)malloc(sizeof(List));
    if (!list) return NULL;
    list->data = (int *)calloc(size, sizeof(int));
    if (!list->data) {
        free(list);
        return NULL;
    }
    list->size = size;
    return list;
}

ListOfLists* zip_lists(const ListOfLists *a, const ListOfLists *b, size_t n) {
    if (a->count != b->count || a->count != n) return NULL;
    ListOfLists *result = create_list_of_lists(n);
    if (!result) return NULL;

    for (size_t i = 0; i < n; ++i) {
        result->lists[i] = create_list(a->lists[i]->size + b->lists[i]->size);
        if (!result->lists[i]) {
            free_list_of_lists(result);
            return NULL;
        }
        for (size_t j = 0; j < a->lists[i]->size; ++j) {
            result->lists[i]->data[j] = a->lists[i]->data[j];
        }
        for (size_t j = 0; j < b->lists[i]->size; ++j) {
            result->lists[i]->data[a->lists[i]->size + j] = b->lists[i]->data[j];
        }
    }
    return result;
}

void print_list(const List *list) {
    for (size_t i = 0; i < list->size; ++i) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

void print_list_of_lists(const ListOfLists *lol) {
    for (size_t i = 0; i < lol->count; ++i) {
        print_list(lol->lists[i]);
    }
}

int main() {
    ListOfLists *a = create_list_of_lists(3);
    a->lists[0] = create_list(2);
    a->lists[0]->data[0] = 1;
    a->lists[0]->data[1] = 2;
    a->lists[1] = create_list(2);
    a->lists[1]->data[0] = 3;
    a->lists[1]->data[1] = 4;
    a->lists[2] = create_list(2);
    a->lists[2]->data[0] = 5;
    a->lists[2]->data[1] = 6;

    ListOfLists *b = create_list_of_lists(3);
    b->lists[0] = create_list(2);
    b->lists[0]->data[0] = 7;
    b->lists[0]->data[1] = 8;
    b->lists[1] = create_list(2);
    b->lists[1]->data[0] = 9;
    b->lists[1]->data[1] = 10;
    b->lists[2] = create_list(2);
    b->lists[2]->data[0] = 11;
    b->lists[2]->data[1] = 12;

    ListOfLists *result = zip_lists(a, b, 3);

    print_list_of_lists(result);

    free_list_of_lists(a);
    free_list_of_lists(b);
    free_list_of_lists(result);

    return 0;
}