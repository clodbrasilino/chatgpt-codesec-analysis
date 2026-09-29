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
    if (lol == NULL) return NULL;
    lol->lists = (List **)malloc(count * sizeof(List *));
    if (lol->lists == NULL) {
        free(lol);
        return NULL;
    }
    lol->count = count;
    for (size_t i = 0; i < count; ++i) {
        lol->lists[i] = (List *)malloc(sizeof(List));
        if (lol->lists[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(lol->lists[j]);
            }
            free(lol->lists);
            free(lol);
            return NULL;
        }
        lol->lists[i]->data = NULL;
        lol->lists[i]->size = 0;
    }
    return lol;
}

void free_list_of_lists(ListOfLists *lol) {
    if (lol != NULL) {
        for (size_t i = 0; i < lol->count; ++i) {
            if (lol->lists[i] != NULL) {
                free(lol->lists[i]->data);
                free(lol->lists[i]);
            }
        }
        free(lol->lists);
        free(lol);
    }
}

ListOfLists* zip_lists(const ListOfLists *a, const ListOfLists *b) {
    if (a->count != b->count) return NULL;
    ListOfLists *result = create_list_of_lists(a->count);
    if (result == NULL) return NULL;
    for (size_t i = 0; i < a->count; ++i) {
        result->lists[i]->data = (int *)malloc((a->lists[i]->size + b->lists[i]->size) * sizeof(int));
        if (result->lists[i]->data == NULL) {
            free_list_of_lists(result);
            return NULL;
        }
        result->lists[i]->size = a->lists[i]->size + b->lists[i]->size;
        for (size_t j = 0; j < a->lists[i]->size; ++j) {
            result->lists[i]->data[j] = a->lists[i]->data[j];
        }
        for (size_t j = 0; j < b->lists[i]->size; ++j) {
            result->lists[i]->data[a->lists[i]->size + j] = b->lists[i]->data[j];
        }
    }
    return result;
}

int main() {
    ListOfLists *a = create_list_of_lists(2);
    a->lists[0]->data = (int[]){1, 2};
    a->lists[0]->size = 2;
    a->lists[1]->data = (int[]){3, 4};
    a->lists[1]->size = 2;

    ListOfLists *b = create_list_of_lists(2);
    b->lists[0]->data = (int[]){5, 6};
    b->lists[0]->size = 2;
    b->lists[1]->data = (int[]){7, 8};
    b->lists[1]->size = 2;

    ListOfLists *zipped = zip_lists(a, b);

    if (zipped != NULL) {
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