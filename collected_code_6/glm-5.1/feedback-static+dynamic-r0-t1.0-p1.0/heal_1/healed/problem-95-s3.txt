#include <stdio.h>
#include <stdlib.h>

int find_min_length(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return 0;
    }

    int min_len = (int)size;
    size_t current_len = 0;
    size_t i = 0;

    while (i < size) {
        if (list[i] != 0) {
            current_len++;
        } else {
            if (current_len > 0 && current_len < (size_t)min_len) {
                min_len = (int)current_len;
            }
            current_len = 0;
        }
        i++;
    }

    if (current_len > 0 && current_len < (size_t)min_len) {
        min_len = (int)current_len;
    }

    return min_len;
}

int main(void) {
    int list1[] = {0, 1, 1, 0, 0, 1, 0, 1, 1, 1};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    int min1 = find_min_length(list1, size1);
    printf("%d\n", min1);

    int list2[] = {0, 0, 0};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    int min2 = find_min_length(list2, size2);
    printf("%d\n", min2);

    int list3[] = {1, 2, 3};
    size_t size3 = sizeof(list3) / sizeof(list3[0]);
    int min3 = find_min_length(list3, size3);
    printf("%d\n", min3);

    int *list4 = NULL;
    size_t size4 = 0;
    int min4 = find_min_length(list4, size4);
    printf("%d\n", min4);

    return 0;
}