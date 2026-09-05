#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
bool are_elements_same(int *list, size_t size) {
    if (list == NULL || size == 0) {
        return true;
    }

    int first = list[0];
    for (size_t i = 1; i < size; i++) {
        if (list[i] != first) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int list1[] = {1, 1, 1, 1};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);

    int list2[] = {1, 2, 1, 1};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);

    int list3[] = {5};
    size_t size3 = sizeof(list3) / sizeof(list3[0]);

    printf("%d\n", are_elements_same(list1, size1));
    printf("%d\n", are_elements_same(list2, size2));
    printf("%d\n", are_elements_same(list3, size3));
    printf("%d\n", are_elements_same(NULL, 0));

    return 0;
}