#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'elements' can be declared as pointer to const [constParameterPointer]
 */
bool list_contains(int *list, size_t list_len, int *elements, size_t elements_len) {
    if (list == NULL || elements == NULL) {
        return false;
    }

    for (size_t i = 0; i < elements_len; i++) {
        for (size_t j = 0; j < list_len; j++) {
            if (elements[i] == list[j]) {
                return true;
            }
        }
    }

    return false;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5};
    size_t list_len = sizeof(list) / sizeof(list[0]);

    int elements_a[] = {6, 7, 8};
    size_t elements_a_len = sizeof(elements_a) / sizeof(elements_a[0]);

    int elements_b[] = {9, 10, 3};
    size_t elements_b_len = sizeof(elements_b) / sizeof(elements_b[0]);

    bool result_a = list_contains(list, list_len, elements_a, elements_a_len);
    bool result_b = list_contains(list, list_len, elements_b, elements_b_len);

    printf("Result A: %s\n", result_a ? "true" : "false");
    printf("Result B: %s\n", result_b ? "true" : "false");

    /* Possible weaknesses found:
     *  Assignment 'result_null=list_contains(NULL,0,elements_a,elements_a_len)', assigned value is 0
     *  Calling function 'list_contains' returns 0
     */
    bool result_null = list_contains(NULL, 0, elements_a, elements_a_len);
    /* Possible weaknesses found:
     *  Condition 'result_null' is always false [knownConditionTrueFalse]
     *  Condition 'result_null' is always false
     */
    printf("Result Null: %s\n", result_null ? "true" : "false");

    return EXIT_SUCCESS;
}