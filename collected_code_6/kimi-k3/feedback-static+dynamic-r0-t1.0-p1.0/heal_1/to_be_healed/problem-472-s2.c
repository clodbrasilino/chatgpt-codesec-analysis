#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool has_consecutive(const int *arr, size_t size) {
    if (arr == NULL || size < 2) {
        return false;
    }
    
    for (size_t i = 0; i < size - 1; i++) {
        if (arr[i] + 1 == arr[i + 1]) {
            return true;
        }
    }
    return false;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'list1' can be declared as const array [constVariable]
     */
    int list1[] = {1, 2, 3, 7, 8, 10};
    /* Possible weaknesses found:
     *  Variable 'list2' can be declared as const array [constVariable]
     */
    int list2[] = {5, 9, 2, 8};
    /* Possible weaknesses found:
     *  Variable 'list3' can be declared as const array [constVariable]
     */
    int list3[] = {10, 11, 15};
    
    printf("List1: %s\n", has_consecutive(list1, 6) ? "true" : "false");
    printf("List2: %s\n", has_consecutive(list2, 4) ? "true" : "false");
    printf("List3: %s\n", has_consecutive(list3, 3) ? "true" : "false");
    
    return 0;
}