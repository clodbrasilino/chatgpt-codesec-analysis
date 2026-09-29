#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool check_even_indices_even(const int *arr, size_t length) {
    if (arr == NULL) {
        return false;
    }
    
    for (size_t i = 0; i < length; i += 2) {
        if (arr[i] % 2 != 0) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int test1[] = {2, 1, 4, 3, 6, 5};
    int test2[] = {2, 1, 3, 5, 6, 7};
    int test3[] = {0, 1, 2, 3, 4, 5};
    int test4[] = {1, 2, 3, 4, 5, 6};
    const int empty[] = {0};
    
    bool null_result = check_even_indices_even(NULL, 5);
    
    printf("Test 1: %s\n", check_even_indices_even(test1, sizeof(test1) / sizeof(test1[0])) ? "true" : "false");
    printf("Test 2: %s\n", check_even_indices_even(test2, sizeof(test2) / sizeof(test2[0])) ? "true" : "false");
    printf("Test 3: %s\n", check_even_indices_even(test3, sizeof(test3) / sizeof(test3[0])) ? "true" : "false");
    printf("Test 4: %s\n", check_even_indices_even(test4, sizeof(test4) / sizeof(test4[0])) ? "true" : "false");
    printf("Empty: %s\n", check_even_indices_even(empty, 0) ? "true" : "false");
    printf("NULL: %s\n", null_result ? "true" : "false");
    
    return 0;
}