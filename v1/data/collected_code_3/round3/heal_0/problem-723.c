#include <stdio.h>

int count_same_pairs(int *list1, int *list2, int size) {
    int count = 0;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(list1[i] == list2[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 3, 4, 5, 6};
    int size = sizeof(list1) / sizeof(list1[0]);

    int count = count_same_pairs(list1, list2, size);
    printf("Number of same pairs: %d\n", count);

    return 0;
}