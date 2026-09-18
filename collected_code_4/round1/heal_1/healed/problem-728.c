#include <stdio.h>
#include <stdlib.h>

int* sumOfLists(int* list1, int* list2, int size) {
    int* sumList = (int*)malloc(size * sizeof(int));
    if(sumList == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    for(int i=0; i<size; i++) {
        sumList[i] = list1[i] + list2[i];
    }
    return sumList;
}

int main() {
    int size = 5;
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {6, 7, 8, 9, 10};

    int* sumList = sumOfLists(list1, list2, size);
    if (sumList == NULL) {
        printf("Summation failed.\n");
        return -1;
    }

    for(int i=0; i<size; i++) {
        printf("%d ", sumList[i]);
    }
    printf("\n");

    free(sumList);
    return 0;
}