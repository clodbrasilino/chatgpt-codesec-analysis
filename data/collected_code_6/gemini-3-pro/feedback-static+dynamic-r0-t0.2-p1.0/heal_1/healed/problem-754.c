#include <stdio.h>
#include <stdlib.h>

void find_common_elements(const int *list1, size_t size1, const int *list2, size_t size2, const int *list3, size_t size3) {
    if (!list1 || !list2 || !list3) {
        return;
    }

    size_t min_size = size1;
    if (size2 < min_size) min_size = size2;
    if (size3 < min_size) min_size = size3;

    for (size_t i = 0; i < min_size; i++) {
        if (list1[i] == list2[i] && list2[i] == list3[i]) {
            printf("Index %zu: %d\n", i, list1[i]);
        }
    }
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5, 6};
    int list2[] = {1, 9, 3, 4, 8};
    int list3[] = {1, 2, 3, 4, 5, 7, 8};

    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    size_t size3 = sizeof(list3) / sizeof(list3[0]);

    find_common_elements(list1, size1, list2, size2, list3, size3);

    return 0;
}