#include <stdio.h>
#include <stdlib.h>

void multiply_lists(int* list1, int* list2, int* result, int size) {
    if(list1 == NULL || list2 == NULL || result == NULL) {
        printf("Error: NULL pointer in multiply_lists function\n");
        return;
    }

    for(int i=0; i<size; i++) {
        result[i] = list1[i]*list2[i];
    }
}

int main() {
    int size = 5;
    int* list1 = malloc(sizeof(int)*size);
    int* list2 = malloc(sizeof(int)*size);
    int* result = malloc(sizeof(int)*size);

    if(list1 == NULL || list2 == NULL || result == NULL) {
        printf("Error: cannot allocate memory\n");
        return -1;
    }

    for(int i=0; i<size; i++) {
        list1[i] = i+1;
        list2[i] = i+2;
    }

    multiply_lists(list1, list2, result, size);

    for(int i=0; i<size; i++) {
        printf("%d ", result[i]);
    }

    free(list1);
    free(list2);
    free(result);

    return 0;
}