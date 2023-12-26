#include <stdio.h>

int countSamePair(const int list1[], const int list2[], const int list3[], int size) {
    int count = 0;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (list1[i] == list2[j]) {
                for (int k = 0; k < size; k++) {
                    if (list1[i] == list3[k]) {
                        count++;
                    }
                }
            }
        }
    }
    
    return count;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 3, 4, 5, 6};
    int list3[] = {3, 4, 5, 6, 7};
    int size = sizeof(list1) / sizeof(list1[0]);
    
    int result = countSamePair(list1, list2, list3, size);
    
    printf("Number of same pairs: %d\n", result);
    
    return 0;
}