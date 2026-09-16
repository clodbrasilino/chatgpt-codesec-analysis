#include <stdio.h>
#include <stdlib.h>

int checkOddIndices(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return 0;
    }
    
    for (int i = 1; i < size; i += 2) {
        if (arr[i] % 2 == 0) {
            return 0;
        }
    }
    
    return 1;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'test1' can be declared as const array [constVariable]
     */
    int test1[] = {2, 3, 4, 5, 6, 7};
    /* Possible weaknesses found:
     *  Variable 'test2' can be declared as const array [constVariable]
     */
    int test2[] = {2, 4, 4, 6, 6, 8};
    /* Possible weaknesses found:
     *  Variable 'test3' can be declared as const array [constVariable]
     */
    int test3[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    /* Possible weaknesses found:
     *  Variable 'test4' can be declared as const array [constVariable]
     */
    int test4[] = {1, 2, 3, 4, 5, 6};
    /* Possible weaknesses found:
     *  Variable 'test5' can be declared as const array [constVariable]
     */
    int test5[] = {5};
    
    printf("Test 1: %d\n", checkOddIndices(test1, 6));
    printf("Test 2: %d\n", checkOddIndices(test2, 6));
    printf("Test 3: %d\n", checkOddIndices(test3, 10));
    printf("Test 4: %d\n", checkOddIndices(test4, 6));
    printf("Test 5: %d\n", checkOddIndices(test5, 1));
    printf("Test 6 (NULL): %d\n", checkOddIndices(NULL, 5));
    printf("Test 7 (zero size): %d\n", checkOddIndices(test1, 0));
    
    return 0;
}