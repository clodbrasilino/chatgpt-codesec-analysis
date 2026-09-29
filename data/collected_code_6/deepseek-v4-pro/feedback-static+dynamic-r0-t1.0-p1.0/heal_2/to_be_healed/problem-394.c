#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_distinct(const int *tuple, size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (tuple[i] == tuple[j]) {
                return false;
            }
        }
    }
    return true;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'test1' can be declared as const array [constVariable]
     */
    int test1[] = {1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  Variable 'test2' can be declared as const array [constVariable]
     */
    int test2[] = {1, 2, 3, 2, 5};
    /* Possible weaknesses found:
     *  Variable 'test3' can be declared as const array [constVariable]
     */
    int test3[] = {42};
    /* Possible weaknesses found:
     *  Variable 'test4' can be declared as pointer to const [constVariablePointer]
     */
    int *test4 = NULL;

    printf("%d\n", is_distinct(test1, 5));
    printf("%d\n", is_distinct(test2, 5));
    printf("%d\n", is_distinct(test3, 1));
    printf("%d\n", is_distinct(test4, 0));

    return 0;
}