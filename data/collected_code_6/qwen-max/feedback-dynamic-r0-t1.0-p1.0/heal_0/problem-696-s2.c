#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int* data;
    int size;
} List;

typedef struct ListOfLists {
    List** lists;
    int count;
} ListOfLists;

ListOfLists* createListOfLists(int count) {
    ListOfLists* lol = (ListOfLists*)malloc(sizeof(ListOfLists));
    if (lol == NULL) exit(EXIT_FAILURE);
    lol->lists = (List**)malloc(count * sizeof(List*));
    if (lol->lists == NULL) exit(EXIT_FAILURE);
    lol->count = count;
    for (int i = 0; i < count; ++i) {
        lol->lists[i] = NULL;
    }
    return lol;
}

void freeListOfLists(ListOfLists* lol) {
    for (int i = 0; lol && (i < lol->count); ++i) {
        if (lol->lists[i]) {
            free(lol->lists[i]->data);
            free(lol->lists[i]);
        }
    }
    free(lol->lists);
    free(lol);
}

List* createList(int size) {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) exit(EXIT_FAILURE);
    list->data = (int*)malloc(size * sizeof(int));
    if (list->data == NULL) exit(EXIT_FAILURE);
    list->size = size;
    return list;
}

ListOfLists* zipLists(ListOfLists* lol1, ListOfLists* lol2) {
    ListOfLists* zipped = createListOfLists(lol1->count * lol2->count);
    int index = 0;
    for (int i = 0; i < lol1->count; ++i) {
        for (int j = 0; j < lol2->count; ++j) {
            zipped->lists[index] = createList(lol1->lists[i]->size + lol2->lists[j]->size);
            for (int k = 0; k < lol1->lists[i]->size; ++k) {
                zipped->lists[index]->data[k] = lol1->lists[i]->data[k];
            }
            for (int k = 0; k < lol2->lists[j]->size; ++k) {
                zipped->lists[index]->data[lol1->lists[i]->size + k] = lol2->lists[j]->data[k];
            }
            ++index;
        }
    }
    return zipped;
}

int main() {
    ListOfLists* lol1 = createListOfLists(2);
    lol1->lists[0] = createList(3);
    lol1->lists[0]->data[0] = 1;
    lol1->lists[0]->data[1] = 2;
    lol1->lists[0]->data[2] = 3;

    lol1->lists[1] = createList(4);
    lol1->lists[1]->data[0] = 4;
    lol1->lists[1]->data[1] = 5;
    lol1->lists[1]->data[2] = 6;
    lol1->lists[1]->data[3] = 7;

    ListOfLists* lol2 = createListOfLists(2);
    lol2->lists[0] = createList(2);
    lol2->lists[0]->data[0] = 8;
    lol2->lists[0]->data[1] = 9;

    lol2->lists[1] = createList(3);
    lol2->lists[1]->data[0] = 10;
    lol2->lists[1]->data[1] = 11;
    lol2->lists[1]->data[2] = 12;

    ListOfLists* zipped = zipLists(lol1, lol2);

    for (int i = 0; i < zipped->count; ++i) {
        for (int j = 0; j < zipped->lists[i]->size; ++j) {
            printf("%d ", zipped->lists[i]->data[j]);
        }
        printf("\n");
    }

    freeListOfLists(zipped);
    freeListOfLists(lol1);
    freeListOfLists(lol2);

    return 0;
}