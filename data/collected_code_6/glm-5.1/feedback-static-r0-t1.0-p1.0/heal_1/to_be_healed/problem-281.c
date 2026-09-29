#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
bool are_elements_unique(int *list, size_t size) {
    if (list == NULL || size == 0) {
        return true;
    }

    int *sorted = malloc(size * sizeof(int));
    if (sorted == NULL) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        sorted[i] = list[i];
    }

    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    for (size_t i = 0; i < size - 1; i++) {
        if (sorted[i] == sorted[i + 1]) {
            free(sorted);
            return false;
        }
    }

    free(sorted);
    return true;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {1, 2, 3, 4, 1};
    int list3[] = {10};
    int *list4 = NULL;

    bool res1 = are_elements_unique(list1, sizeof(list1) / sizeof(list1[0]));
    bool res2 = are_elements_unique(list2, sizeof(list2) / sizeof(list2[0]));
    bool res3 = are_elements_unique(list3, sizeof(list3) / sizeof(list3[0]));
    /* Possible weaknesses found:
     *  Calling function 'are_elements_unique' returns 1
     *  Assignment 'res4=are_elements_unique(list4,0)', assigned value is 1
     */
    bool res4 = are_elements_unique(list4, 0);

    printf("List 1 unique: %s\n", res1 ? "true" : "false");
    printf("List 2 unique: %s\n", res2 ? "true" : "false");
    printf("List 3 unique: %s\n", res3 ? "true" : "false");
    /* Possible weaknesses found:
     *  Condition 'res4' is always true [knownConditionTrueFalse]
     *  Condition 'res4' is always true
     */
    printf("List 4 unique: %s\n", res4 ? "true" : "false");

    return 0;
}