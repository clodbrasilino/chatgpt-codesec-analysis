#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool has_common_element(const int *list1, size_t size1, const int *list2, size_t size2);

bool has_common_element(const int *list1, size_t size1, const int *list2, size_t size2) {
    if (list1 == NULL || list2 == NULL || size1 == 0 || size2 == 0) {
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
    int list_b[] = {8, 7, 6, 2, 9};
    int list_c[] = {10, 11, 12};

    size_t size_a = sizeof(list_a) / sizeof(list_a[0]);
    size_t size_b = sizeof(list_b) / sizeof(list_b[0]);
    size_t size_c = sizeof(list_c) / sizeof(list_c[0]);

    bool result_ab = has_common_element(list_a, size_a, list_b, size_b);
    bool result_ac = has_common_element(list_a, size_a, list_c, size_c);

    printf("%d\n", result_ab);
    printf("%d\n", result_ac);

    return 0;
}