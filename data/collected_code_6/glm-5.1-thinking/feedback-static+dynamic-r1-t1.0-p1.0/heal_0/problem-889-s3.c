#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} List;

typedef struct {
    List *lists;
    size_t count;
} ListOfLists;

void reverse_list(List *list) {
    if (list == NULL || list->data == NULL || list->size < 2) {
        return;
    }
    size_t left = 0;
    size_t right = list->size - 1;
    while (left < right) {
        int temp = list->data[left];
        list->data[left] = list->data[right];
        list->data[right] = temp;
        left++;
        right--;
    }
}

void reverse_each_list(ListOfLists *lol) {
    if (lol == NULL || lol->lists == NULL) {
        return;
    }
    for (size_t i = 0; i < lol->count; i++) {
        reverse_list(&lol->lists[i]);
    }
}

int main(void) {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5, 6, 7};
    int data3[] = {8, 9};

    ListOfLists lol;
    lol.count = 3;
    lol.lists = malloc(sizeof(List) * lol.count);
    if (lol.lists == NULL) {
        return EXIT_FAILURE;
    }

    lol.lists[0].data = data1;
    lol.lists[0].size = 3;
    lol.lists[1].data = data2;
    lol.lists[1].size = 4;
    lol.lists[2].data = data3;
    lol.lists[2].size = 2;

    reverse_each_list(&lol);

    for (size_t i = 0; i < lol.count; i++) {
        for (size_t j = 0; j < lol.lists[i].size; j++) {
            printf("%d ", lol.lists[i].data[j]);
        }
        printf("\n");
    }

    free(lol.lists);

    return EXIT_SUCCESS;
}