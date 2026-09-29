#include <stdio.h>
#include <stdbool.h>

bool has_common_element(const int *list1, size_t size1, const int *list2, size_t size2) {
    if (list1 == NULL || list2 == NULL) {
        return false;
    }

    for (size_t i = 0; i < size1; i++) {
        for (size_t j = 0; j < size2; j++) {
            if (list1[i] == list2[j]) {
                return true;
            }
        }
    }

    return false;
}

int main(void) {
    int list_a[] = {1, 2, 3, 4, 5};
    int list_b[] = {5, 6, 7, 8, 9};
    int list_c[] = {10, 11, 12};

    size_t size_a = sizeof(list_a) / sizeof(list_a[0]);
    size_t size_b = sizeof(list_b) / sizeof(list_b[0]);
    size_t size_c = sizeof(list_c) / sizeof(list_c[0]);

    bool result1 = has_common_element(list_a, size_a, list_b, size_b);
    bool result2 = has_common_element(list_a, size_a, list_c, size_c);

    printf("%d\n", result1);
    printf("%d\n", result2);

    return 0;
}