#include <stdio.h>
#include <stdlib.h>

int count_same_pairs(int *list1, int size1, int *list2, int size2, int *list3, int size3) {
    int count = 0;
    int i = 0, j = 0, k = 0;
    
    while (i < size1 && j < size2 && k < size3) {
        if (list1[i] == list2[j] && list2[j] == list3[k]) {
            count++;
            i++;
            j++;
            k++;
        }
        else if (list1[i] < list2[j]) {
            i++;
        }
        else if (list2[j] < list3[k]) {
            j++;
        }
        else {
            k++;
        }
    }
    
    return count;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 3, 4, 5, 6};
    int list3[] = {3, 4, 5, 6, 7};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int size3 = sizeof(list3) / sizeof(list3[0]);
    
    int result = count_same_pairs(list1, size1, list2, size2, list3, size3);
    printf("Number of same pairs: %d\n", result);
    
    return 0;
}