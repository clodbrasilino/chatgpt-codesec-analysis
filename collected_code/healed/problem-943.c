#include <stdio.h>

void merge(const int list1[], int size1, const int list2[], int size2, int mergedList[]) {
    int i = 0, j = 0, k = 0;
    
    while (i < size1 && j < size2) {
        if (list1[i] < list2[j]) {
            mergedList[k++] = list1[i++];
        } else {
            mergedList[k++] = list2[j++];
        }
    }
    
    while (i < size1) {
        mergedList[k++] = list1[i++];
    }
    
    while (j < size2) {
        mergedList[k++] = list2[j++];
    }
}

int main() {
    const int list1[] = {1, 4, 6, 8, 10};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    
    const int list2[] = {2, 3, 5, 7, 9};
    int size2 = sizeof(list2) / sizeof(list2[0]);
    
    int mergedList[size1 + size2];
    
    merge(list1, size1, list2, size2, mergedList);
    
    printf("Merged List: ");
    for (int i = 0; i < size1 + size2; i++) {
        printf("%d ", mergedList[i]);
    }
    printf("\n");
    
    return 0;
}