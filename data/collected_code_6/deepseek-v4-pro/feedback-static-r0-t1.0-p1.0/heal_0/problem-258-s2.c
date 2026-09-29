#include <stdio.h>

int countOddElements(int list[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] % 2 != 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int testList1[] = {1, 2, 3, 4, 5};
    int size1 = sizeof(testList1) / sizeof(testList1[0]);
    printf("%d\n", countOddElements(testList1, size1));
    
    int testList2[] = {2, 4, 6, 8};
    int size2 = sizeof(testList2) / sizeof(testList2[0]);
    printf("%d\n", countOddElements(testList2, size2));
    
    int testList3[] = {-3, -2, -1, 0, 1, 2, 3};
    int size3 = sizeof(testList3) / sizeof(testList3[0]);
    printf("%d\n", countOddElements(testList3, size3));
    
    return 0;
}