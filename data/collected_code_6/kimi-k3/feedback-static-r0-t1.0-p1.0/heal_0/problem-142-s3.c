#include <stdio.h>
#include <stdlib.h>

int count_same_pairs(int *list1, int *list2, int *list3, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list1[i] == list2[i] && list2[i] == list3[i]) {
            count++;
        }
    }
    return count;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {1, 2, 3, 4, 5};
    int list3[] = {1, 2, 3, 4, 5};
    int size = sizeof(list1) / sizeof(list1[0]);

    int result = count_same_pairs(list1, list2, list3, size);
    printf("Number of same pairs: %d\n", result);

    return 0;
}