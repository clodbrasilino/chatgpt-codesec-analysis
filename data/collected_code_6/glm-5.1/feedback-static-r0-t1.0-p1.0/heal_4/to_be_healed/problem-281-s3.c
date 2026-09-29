#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool are_elements_unique(const int *list, size_t size) {
    if (list == NULL) {
        return true;
    }

    if (size < 2) {
        return true;
    }

    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (list[i] == list[j]) {
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);

    int list2[] = {1, 2, 3, 2, 5};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);

    int list3[] = {7};
    size_t size3 = sizeof(list3) / sizeof(list3[0]);

    const int *list4 = NULL;
    size_t size4 = 0;

    if (are_elements_unique(list1, size1)) {
        printf("List 1: Unique\n");
    } else {
        printf("List 1: Not Unique\n");
    }

    if (are_elements_unique(list2, size2)) {
        printf("List 2: Unique\n");
    } else {
        printf("List 2: Not Unique\n");
    }

    if (are_elements_unique(list3, size3)) {
        printf("List 3: Unique\n");
    } else {
        printf("List 3: Not Unique\n");
    }

    /* Possible weaknesses found:
     *  Condition 'are_elements_unique(list4,size4)' is always true
     *  Calling function 'are_elements_unique' returns 1
     *  Condition 'are_elements_unique(list4,size4)' is always true [knownConditionTrueFalse]
     */
    if (are_elements_unique(list4, size4)) {
        printf("List 4: Unique\n");
    } else {
        printf("List 4: Not Unique\n");
    }

    return 0;
}