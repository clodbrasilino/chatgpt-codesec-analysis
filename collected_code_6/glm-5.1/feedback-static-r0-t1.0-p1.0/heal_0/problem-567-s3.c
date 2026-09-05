#include <stdio.h>
#include <stdbool.h>

bool is_sorted(int *list, size_t size) {
    if (list == NULL || size <= 1) {
        return true;
    }

    for (size_t i = 0; i < size - 1; i++) {
        if (list[i] > list[i + 1]) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);

    int list2[] = {5, 3, 1, 4, 2};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);

    int list3[] = {10};
    size_t size3 = sizeof(list3) / sizeof(list3[0]);
    
    int list4[] = {2, 2, 2, 2};
    size_t size4 = sizeof(list4) / sizeof(list4[0]);

    printf("%d\n", is_sorted(list1, size1));
    printf("%d\n", is_sorted(list2, size2));
    printf("%d\n", is_sorted(list3, size3));
    printf("%d\n", is_sorted(list4, size4));
    printf("%d\n", is_sorted(NULL, 0));

    return 0;
}