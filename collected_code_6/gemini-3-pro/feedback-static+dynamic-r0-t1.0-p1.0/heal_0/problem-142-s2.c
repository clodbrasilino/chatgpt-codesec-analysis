#include <stdio.h>
#include <stdlib.h>

int count_same_pairs(const int* list1, size_t size1, const int* list2, size_t size2, const int* list3, size_t size3) {
    if (list1 == NULL || list2 == NULL || list3 == NULL) {
        return 0;
    }

    size_t min_size = size1 < size2 ? size1 : size2;
    min_size = min_size < size3 ? min_size : size3;

    int count = 0;
    for (size_t i = 0; i < min_size; ++i) {
        if (list1[i] == list2[i] && list2[i] == list3[i]) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {1, 2, 0, 4, 5};
    int list3[] = {1, 2, 3, 4, 6};

    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    size_t size3 = sizeof(list3) / sizeof(list3[0]);

    int result = count_same_pairs(list1, size1, list2, size2, list3, size3);

    printf("Count of same pairs: %d\n", result);

    return 0;
}