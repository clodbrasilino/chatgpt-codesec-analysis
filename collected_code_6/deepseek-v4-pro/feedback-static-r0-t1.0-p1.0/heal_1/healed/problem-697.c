#include <stdio.h>
#include <stdlib.h>

int count_even(const int *list, int size) {
    if (list == NULL || size <= 0) {
        return -1;
    }
    
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] % 2 == 0) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5, 6};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int result1 = count_even(list1, size1);
    
    if (result1 != -1) {
        printf("Even count: %d\n", result1);
    } else {
        printf("Error: Invalid input\n");
    }
    
    int list2[] = {2, 4, 6, 8};
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int result2 = count_even(list2, size2);
    
    if (result2 != -1) {
        printf("Even count: %d\n", result2);
    } else {
        printf("Error: Invalid input\n");
    }
    
    printf("Error: Invalid input\n");
    
    int list4[] = {1, 3, 5, 7};
    int size4 = sizeof(list4) / sizeof(list4[0]);
    int result4 = count_even(list4, size4);
    
    if (result4 != -1) {
        printf("Even count: %d\n", result4);
    } else {
        printf("Error: Invalid input\n");
    }
    
    return 0;
}