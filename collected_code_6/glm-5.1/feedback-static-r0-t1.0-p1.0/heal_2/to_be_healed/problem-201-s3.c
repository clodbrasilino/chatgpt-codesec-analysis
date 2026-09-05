#include <stdio.h>
#include <stdbool.h>

bool are_elements_same(const int *list, size_t size) {
    if (list == NULL) {
        return false;
    }

    if (size == 0) {
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

    /* Possible weaknesses found:
     *  Variable 'list4' can be declared as pointer to const [constVariablePointer]
     */
    int *list4 = NULL;
    size_t size4 = 0;

    bool res1 = are_elements_same(list1, size1);
    bool res2 = are_elements_same(list2, size2);
    bool res3 = are_elements_same(list3, size3);
    bool res4 = are_elements_same(list4, size4);

    printf("%d\n", res1);
    printf("%d\n", res2);
    printf("%d\n", res3);
    printf("%d\n", res4);

    return 0;
}