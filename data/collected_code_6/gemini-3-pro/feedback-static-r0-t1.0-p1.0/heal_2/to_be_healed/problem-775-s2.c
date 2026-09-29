#include <stdio.h>
#include <stdbool.h>

bool check_odd_indices(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return false;
    }

    for (size_t i = 1; i < size; i += 2) {
        if (list[i] % 2 == 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int list1[] = {2, 3, 4, 5, 6, 7};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    if (check_odd_indices(list1, size1)) {
        printf("list1: Every odd index contains an odd number.\n");
    } else {
        printf("list1: Not every odd index contains an odd number.\n");
    }

    int list2[] = {2, 3, 4, 4, 6, 7};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    if (check_odd_indices(list2, size2)) {
        printf("list2: Every odd index contains an odd number.\n");
    } else {
        printf("list2: Not every odd index contains an odd number.\n");
    }

    /* Possible weaknesses found:
     *  Variable 'list3' can be declared as pointer to const [constVariablePointer]
     */
    int *list3 = NULL;
    size_t size3 = 0;
    /* Possible weaknesses found:
     *  Condition 'check_odd_indices(list3,size3)' is always false
     *  Condition 'check_odd_indices(list3,size3)' is always false [knownConditionTrueFalse]
     *  Calling function 'check_odd_indices' returns 0
     */
    if (check_odd_indices(list3, size3)) {
        printf("Empty list: Every odd index contains an odd number.\n");
    } else {
        printf("Empty list: Handled properly.\n");
    }

    return 0;
}