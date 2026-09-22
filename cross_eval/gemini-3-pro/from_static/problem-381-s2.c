#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
} InnerList;

typedef struct {
    InnerList* lists;
    size_t count;
} ListOfLists;

int sort_index = 0;

int compare_inner_lists(const void* a, const void* b) {
    const InnerList* listA = (const InnerList*)a;
    const InnerList* listB = (const InnerList*)b;

    if (sort_index < 0 || (size_t)sort_index >= listA->size || (size_t)sort_index >= listB->size) {
        return 0;
    }

    int valA = listA->data[sort_index];
    int valB = listB->data[sort_index];

    if (valA < valB) return -1;
    if (valA > valB) return 1;
    return 0;
}

void sort_list_of_lists(ListOfLists* lol, int index) {
    if (lol == NULL || lol->lists == NULL || lol->count == 0 || index < 0) {
        return;
    }
    sort_index = index;
    qsort(lol->lists, lol->count, sizeof(InnerList), compare_inner_lists);
}

void print_list_of_lists(const ListOfLists* lol) {
    if (lol == NULL || lol->lists == NULL) {
        return;
    }
    for (size_t i = 0; i < lol->count; i++) {
        printf("[");
        for (size_t j = 0; j < lol->lists[i].size; j++) {
            printf("%d", lol->lists[i].data[j]);
            if (j < lol->lists[i].size - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(void) {
    int data1[] = {10, 20, 30};
    int data2[] = {5, 25, 15};
    int data3[] = {8, 10, 50};
    int data4[] = {12, 5, 40};

    InnerList lists[4];
    lists[0].data = data1; lists[0].size = 3;
    lists[1].data = data2; lists[1].size = 3;
    lists[2].data = data3; lists[2].size = 3;
    lists[3].data = data4; lists[3].size = 3;

    ListOfLists lol;
    lol.lists = lists;
    lol.count = 4;

    printf("Original:\n");
    print_list_of_lists(&lol);

    sort_list_of_lists(&lol, 1);

    printf("\nSorted by index 1:\n");
    print_list_of_lists(&lol);

    return 0;
}