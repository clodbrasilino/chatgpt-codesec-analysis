#include <stdio.h>
#include <stdlib.h>

int count_same_pairs(const int* list1, const int* list2, const int* list3, int size) {
    if (list1 == NULL || list2 == NULL || list3 == NULL || size <= 0) {
        return 0;
    }

    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list1[i] == list2[i] || list1[i] == list3[i] || list2[i] == list3[i]) {
            count++;
        }
    }
    
    return count;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {1, 2, 8, 4, 9};
    int list3[] = {1, 7, 3, 4, 5};
    int size = sizeof(list1) / sizeof(list1[0]);

    int result = count_same_pairs(list1, list2, list3, size);

    printf("Number of pairs: %d\n", result);

    return 0;
}