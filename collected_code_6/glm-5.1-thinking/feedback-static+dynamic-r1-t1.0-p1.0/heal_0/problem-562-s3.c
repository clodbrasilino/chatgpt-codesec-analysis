#include <stdio.h>
#include <stddef.h>

size_t max_sublist_length(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return 0;
    }

    size_t max_len = 1;
    size_t current_len = 1;

    for (size_t i = 1; i < size; ++i) {
        if (list[i] > list[i - 1]) {
            current_len++;
        } else {
            current_len = 1;
        }
        
        if (current_len > max_len) {
            max_len = current_len;
        }
    }

    return max_len;
}

int main(void) {
    int list1[] = {1, 2, 3, 1, 2, 3, 4, 5, 1};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    printf("%zu\n", max_sublist_length(list1, size1));

    int list2[] = {5, 4, 3, 2, 1};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    printf("%zu\n", max_sublist_length(list2, size2));

    int list3[] = {10};
    size_t size3 = sizeof(list3) / sizeof(list3[0]);
    printf("%zu\n", max_sublist_length(list3, size3));

    printf("%zu\n", max_sublist_length(NULL, 5));

    printf("%zu\n", max_sublist_length(list1, 0));

    return 0;
}