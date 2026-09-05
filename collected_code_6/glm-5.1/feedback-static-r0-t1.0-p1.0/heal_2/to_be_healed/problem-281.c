#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool are_elements_unique(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return false;
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
    /* Possible weaknesses found:
     *  Assignment 'list4=NULL', assigned value is 0
     */
    int *list4 = NULL;
    size_t size4 = 5;
    
    /* Possible weaknesses found:
     *  Condition 'list4==NULL' is always true
     *  Condition 'list4==NULL' is always true [knownConditionTrueFalse]
     */
    if (list4 == NULL) {
        list4 = malloc(size4 * sizeof(int));
        if (list4 != NULL) {
            for (size_t i = 0; i < size4; i++) {
                list4[i] = (int)i;
            }
        }
    }

    bool res1 = are_elements_unique(list1, sizeof(list1) / sizeof(list1[0]));
    bool res2 = are_elements_unique(list2, sizeof(list2) / sizeof(list2[0]));
    bool res3 = are_elements_unique(list3, sizeof(list3) / sizeof(list3[0]));
    bool res4 = are_elements_unique(list4, size4);

    printf("List 1 unique: %s\n", res1 ? "true" : "false");
    printf("List 2 unique: %s\n", res2 ? "true" : "false");
    printf("List 3 unique: %s\n", res3 ? "true" : "false");
    printf("List 4 unique: %s\n", res4 ? "true" : "false");
    
    free(list4);

    return 0;
}