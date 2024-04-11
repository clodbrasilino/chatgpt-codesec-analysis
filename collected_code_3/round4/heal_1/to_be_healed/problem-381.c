#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int arr[MAX];
    int len;
} List;

int compare(const void* a, const void* b, void* arg) {
    int index = *(int*)arg;
    List* listA = (List*)a;
    List* listB = (List*)b;
    return listA->arr[index] - listB->arr[index];
}

void sortListOfLists(List* lists, int len, int index) {
    /* Possible weaknesses found:
     *  passing argument 5 of 'qsort_r' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    qsort_r(lists, len, sizeof(List), compare, &index);
}

int main() {
    List lists[MAX];
    int len = 5;
    int index = 2;

    for(int i = 0; i < len; i++) {
        for(int j = 0; j < MAX; j++) {
            lists[i].arr[j] = rand() % 100;
        }
        lists[i].len = MAX;
    }

    sortListOfLists(lists, len, index);

    for(int i = 0; i < len; i++) {
        for(int j = 0; j < lists[i].len; j++) {
            printf("%d ", lists[i].arr[j]);
        }
        printf("\n");
    }

    return 0;
}