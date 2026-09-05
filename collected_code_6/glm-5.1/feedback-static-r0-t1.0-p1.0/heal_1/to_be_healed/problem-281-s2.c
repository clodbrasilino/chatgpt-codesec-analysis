#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
bool are_elements_unique(int *list, size_t size) {
    if (list == NULL) {
        return false;
    }

    if (size < 2) {
        return true;
    }

    int *temp = (int *)malloc(size * sizeof(int));
    if (temp == NULL) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        temp[i] = list[i];
    }

    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                int swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    for (size_t i = 0; i < size - 1; i++) {
        if (temp[i] == temp[i + 1]) {
            free(temp);
            return false;
        }
    }

    free(temp);
    return true;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);

    if (are_elements_unique(list1, size1)) {
        printf("List 1 elements are unique.\n");
    } else {
        printf("List 1 elements are not unique.\n");
    }

    int list2[] = {1, 2, 3, 2, 5};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);

    if (are_elements_unique(list2, size2)) {
        printf("List 2 elements are unique.\n");
    } else {
        printf("List 2 elements are not unique.\n");
    }

    int *list3 = NULL;
    size_t size3 = 0;

    /* Possible weaknesses found:
     *  Condition 'are_elements_unique(list3,size3)' is always false
     *  Condition 'are_elements_unique(list3,size3)' is always false [knownConditionTrueFalse]
     *  Calling function 'are_elements_unique' returns 0
     */
    if (are_elements_unique(list3, size3)) {
        printf("List 3 elements are unique.\n");
    } else {
        printf("List 3 elements are not unique.\n");
    }

    return 0;
}