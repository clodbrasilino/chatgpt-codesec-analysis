#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int are_elements_same(int *list, size_t length) {
    if (length == 0)
        return 1;

    int first = list[0];
    for (size_t i = 1; i < length; ++i) {
        if (list[i] != first)
            return 0;
    }
    return 1;
}

int main() {
    int list1[] = {5, 5, 5, 5};
    int list2[] = {5, 6, 5, 5};

    size_t length1 = sizeof(list1) / sizeof(list1[0]);
    size_t length2 = sizeof(list2) / sizeof(list2[0]);

    if (are_elements_same(list1, length1)) {
        printf("All elements in list1 are the same.\n");
    } else {
        printf("Elements in list1 are not the same.\n");
    }

    if (are_elements_same(list2, length2)) {
        printf("All elements in list2 are the same.\n");
    } else {
        printf("Elements in list2 are not the same.\n");
    }

    return 0;
}