#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_subset(const int *tuple1, size_t size1, const int *tuple2, size_t size2) {
    if (tuple1 == NULL || tuple2 == NULL) {
        return false;
    }

    if (size1 == 0) {
        return true;
    }

    for (size_t i = 0; i < size1; i++) {
        bool found = false;
        for (size_t j = 0; j < size2; j++) {
            if (tuple1[i] == tuple2[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }

    return true;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 't1' can be declared as const array [constVariable]
     */
    int t1[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 't2' can be declared as const array [constVariable]
     */
    int t2[] = {1, 2, 3, 4, 5};
    
    bool result1 = is_subset(t1, 3, t2, 5);
    printf("%d\n", result1);

    /* Possible weaknesses found:
     *  Variable 't3' can be declared as const array [constVariable]
     */
    int t3[] = {6, 7};
    bool result2 = is_subset(t3, 2, t2, 5);
    printf("%d\n", result2);

    bool result3 = is_subset(NULL, 3, t2, 5);
    printf("%d\n", result3);

    /* Possible weaknesses found:
     *  Variable 't4' can be declared as const array [constVariable]
     */
    int t4[] = {};
    bool result4 = is_subset(t4, 0, t2, 5);
    printf("%d\n", result4);

    return 0;
}