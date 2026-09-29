#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool contains_sublist(const int *list, int list_size, const int *sublist, int sublist_size) {
    if (sublist_size == 0) {
        return true;
    }
    if (list == NULL || sublist == NULL || list_size < sublist_size) {
        return false;
    }
    for (int i = 0; i <= list_size - sublist_size; i++) {
        bool match = true;
        for (int j = 0; j < sublist_size; j++) {
            if (list[i + j] != sublist[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}

int main(void) {
    const int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    const int sublist1[] = {3, 4, 5};
    const int sublist2[] = {4, 6};
    const int sublist3[] = {9};

    bool result1 = contains_sublist(list, 9, sublist1, 3);
    bool result2 = contains_sublist(list, 9, sublist2, 2);
    bool result3 = contains_sublist(list, 9, sublist3, 1);
    /* Possible weaknesses found:
     *  Calling function 'contains_sublist' returns 1
     *  Assignment 'result4=contains_sublist(list,9,(const int[]){},0)', assigned value is 1
     */
    bool result4 = contains_sublist(list, 9, (const int[]){}, 0);
    /* Possible weaknesses found:
     *  Calling function 'contains_sublist' returns 0
     *  Assignment 'result5=contains_sublist(NULL,9,sublist1,3)', assigned value is 0
     */
    bool result5 = contains_sublist(NULL, 9, sublist1, 3);

    printf("Result 1: %s\n", result1 ? "true" : "false");
    printf("Result 2: %s\n", result2 ? "true" : "false");
    printf("Result 3: %s\n", result3 ? "true" : "false");
    /* Possible weaknesses found:
     *  Condition 'result4' is always true [knownConditionTrueFalse]
     *  Condition 'result4' is always true
     */
    if (result4) {
        printf("Result 4: true\n");
    } else {
        printf("Result 4: false\n");
    }
    /* Possible weaknesses found:
     *  Condition 'result5' is always false [knownConditionTrueFalse]
     *  Condition 'result5' is always false
     */
    if (result5) {
        printf("Result 5: true\n");
    } else {
        printf("Result 5: false\n");
    }

    return 0;
}