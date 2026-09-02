#include <stdio.h>
#include <stdlib.h>

int containsDuplicate(int *arr, int size) {
    if (arr == NULL || size <= 1) {
        return 0;
    }
    
    int i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                return 1;
            }
        }
    }
    
    return 0;
}

int main(void) {
    int test1[] = {1, 2, 3, 4, 5};
    int test2[] = {1, 2, 3, 2, 4};
    int test3[] = {5};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    int size2 = sizeof(test2) / sizeof(test2[0]);
    int size3 = sizeof(test3) / sizeof(test3[0]);
    
    printf("%d\n", containsDuplicate(test1, size1));
    printf("%d\n", containsDuplicate(test2, size2));
    printf("%d\n", containsDuplicate(test3, size3));
    
    return 0;
}