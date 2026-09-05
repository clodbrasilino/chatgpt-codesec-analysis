#include <stdio.h>
#include <stdlib.h>

int check_odd_indices(const int *list, size_t size) {
    if (list == NULL) {
        return 0;
    }
    for (size_t i = 1; i < size; i += 2) {
        if (list[i] % 2 == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int list1[] = {2, 3, 4, 5, 6, 7};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    int result1 = check_odd_indices(list1, size1);
    printf("%d\n", result1);

    int list2[] = {1, 2, 3, 4, 5, 6};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    int result2 = check_odd_indices(list2, size2);
    printf("%d\n", result2);

    int *list3 = NULL;
    size_t size3 = 0;
    int result3 = check_odd_indices(list3, size3);
    printf("%d\n", result3);

    return 0;
}