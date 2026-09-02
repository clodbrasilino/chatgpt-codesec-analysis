#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} List;

List* createList(size_t length) {
    List *list = (List *)malloc(sizeof(List));
    list->data = (int *)malloc(length * sizeof(int));
    list->length = length;
    return list;
}

void freeList(List *list) {
    free(list->data);
    free(list);
}

int* getLastElements(List **sublists, size_t num_sublists) {
    int *last_elements = (int *)malloc(num_sublists * sizeof(int));
    for (size_t i = 0; i < num_sublists; ++i) {
        if (sublists[i]->length > 0) {
            last_elements[i] = sublists[i]->data[sublists[i]->length - 1];
        } else {
            last_elements[i] = 0; // Assuming 0 is a default value for empty lists
        }
    }
    return last_elements;
}

int main() {
    size_t num_sublists = 3;

    List *sublists[3] = {createList(5), createList(3), createList(4)};
    sublists[0]->data[0] = 1; sublists[0]->data[1] = 2; sublists[0]->data[2] = 3; sublists[0]->data[3] = 4; sublists[0]->data[4] = 5;
    sublists[1]->data[0] = 6; sublists[1]->data[1] = 7; sublists[1]->data[2] = 8;
    sublists[2]->data[0] = 9; sublists[2]->data[1] = 10; sublists[2]->data[2] = 11; sublists[2]->data[3] = 12;

    int *last_elements = getLastElements(sublists, num_sublists);

    for (size_t i = 0; i < num_sublists; ++i) {
        printf("%d ", last_elements[i]);
    }
    printf("\n");

    for (size_t i = 0; i < num_sublists; ++i) {
        freeList(sublists[i]);
    }
    free(last_elements);

    return 0;
}