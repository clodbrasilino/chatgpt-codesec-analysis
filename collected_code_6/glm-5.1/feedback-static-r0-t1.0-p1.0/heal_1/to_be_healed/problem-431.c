#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list1' can be declared as pointer to const [constParameterPointer]
 */
bool has_common_element(int *list1, size_t size1, int *list2, size_t size2) {
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
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {6, 7, 8, 9, 10};
    int c[] = {10, 11, 12};
    int d[] = {};
    int *e = NULL;

    size_t size_a = sizeof(a) / sizeof(a[0]);
    size_t size_b = sizeof(b) / sizeof(b[0]);
    size_t size_c = sizeof(c) / sizeof(c[0]);
    size_t size_d = sizeof(d) / sizeof(d[0]);
    size_t size_e = 0;

    printf("%d\n", has_common_element(a, size_a, b, size_b));
    printf("%d\n", has_common_element(a, size_a, c, size_c));
    printf("%d\n", has_common_element(a, size_a, d, size_d));
    printf("%d\n", has_common_element(e, size_e, a, size_a));

    return 0;
}