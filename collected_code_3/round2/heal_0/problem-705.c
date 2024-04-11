#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int len;
} List;

int compare_values(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int compare_lists(const void* a, const void* b) {
    List* listA = (List*)a;
    List* listB = (List*)b;

    if (listA->len != listB->len) {
        return listA->len - listB->len;
    }

    for (int i = 0; i < listA->len; i++) {
        if (listA->data[i] != listB->data[i]) {
            return listA->data[i] - listB->data[i];
        }
    }

    return 0;
}

void sort_list_of_lists(List* lists, int numLists) {
    for (int i = 0; i < numLists; i++) {
        qsort(lists[i].data, lists[i].len, sizeof(int), compare_values);
    }

    qsort(lists, numLists, sizeof(List), compare_lists);
}

int main() {
    int data1[] = {5, 1, 3};
    int data2[] = {2, 4};
    int data3[] = {6, 7, 8, 9};

    List lists[] = {
        {data1, sizeof(data1) / sizeof(int)},
        {data2, sizeof(data2) / sizeof(int)},
        {data3, sizeof(data3) / sizeof(int)}
    };

    sort_list_of_lists(lists, sizeof(lists) / sizeof(List));

    for (int i = 0; i < sizeof(lists) / sizeof(List); i++) {
        for (int j = 0; j < lists[i].len; j++) {
            printf("%d ", lists[i].data[j]);
        }
        printf("\n");
    }

    return 0;
}