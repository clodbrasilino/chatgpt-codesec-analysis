#include <stdio.h>
#include <stdlib.h>

int count_same_pairs(int *list1, int *list2, int *list3, int size1, int size2, int size3) {
    int count = 0;
    
    if (list1 == NULL || list2 == NULL || list3 == NULL) {
        return -1;
    }
    
    if (size1 <= 0 || size2 <= 0 || size3 <= 0) {
        return -1;
    }
    
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            for (int k = 0; k < size3; k++) {
                if (list1[i] == list2[j] && list2[j] == list3[k]) {
                    count++;
                }
            }
        }
    }
    
    return count;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 3, 4, 6, 7};
    int list3[] = {3, 4, 5, 8, 9};
    
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int size3 = sizeof(list3) / sizeof(list3[0]);
    
    int result = count_same_pairs(list1, list2, list3, size1, size2, size3);
    
    if (result >= 0) {
        printf("Count of same pairs: %d\n", result);
    } else {
        printf("Error: Invalid input\n");
    }
    
    return 0;
}