#include <stdio.h>
#include <stdlib.h>

#define LIST_SIZE 20

void sum_two_lists(int* list1, int* list2, int* result, int size) {
    if (list1 == NULL || list2 == NULL || result == NULL) {
        printf("NULL pointer detected.\n");
        exit(1);
    }

    for(int i = 0; i < size; i++){
        result[i] = list1[i] + list2[i];
    }
}

int main(){
    int list1[LIST_SIZE], list2[LIST_SIZE], result[LIST_SIZE];

    for(int i = 0; i < LIST_SIZE; i++){
        list1[i] = i;
        list2[i] = i * 2;
    }

    sum_two_lists(list1, list2, result, LIST_SIZE);

    printf("Result: ");
    for(int i = 0; i < LIST_SIZE; i++){
        printf("%d ", result[i]);
    }

    return 0;
}