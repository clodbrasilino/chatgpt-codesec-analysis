#include <stdio.h>
#include <stdbool.h>

bool check_even_indices(const int *arr, size_t size) {
    if (arr == NULL && size > 0) {
        return false;
    }

    for (size_t i = 0; i < size; i += 2) {
        if (arr[i] % 2 != 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int list1[] = {2, 1, 4, 3, 6};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    
    int list2[] = {2, 1, 5, 3, 6};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);

    if (check_even_indices(list1, size1)) {
        printf("List 1: True\n");
    } else {
        printf("List 1: False\n");
    }

    if (check_even_indices(list2, size2)) {
        printf("List 2: True\n");
    } else {
        printf("List 2: False\n");
    }

    return 0;
}