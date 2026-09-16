#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool check_even_indices_even_values(const int *arr, size_t size)
{
    if (arr == NULL)
    {
        return false;
    }
    
    for (size_t i = 0; i < size; i += 2)
    {
        if (arr[i] % 2 != 0)
        {
            return false;
        }
    }
    return true;
}

int main(void)
{
    int test1[] = {2, 5, 4, 7, 6, 9, 8};
    int test2[] = {2, 5, 3, 7, 6};
    int test3[] = {1, 2, 3};
    int test4[] = {};
    
    bool result1 = check_even_indices_even_values(test1, sizeof(test1) / sizeof(test1[0]));
    bool result2 = check_even_indices_even_values(test2, sizeof(test2) / sizeof(test2[0]));
    bool result3 = check_even_indices_even_values(test3, sizeof(test3) / sizeof(test3[0]));
    bool result4 = check_even_indices_even_values(test4, 0);
    bool result5 = check_even_indices_even_values(NULL, 5);
    
    printf("Test 1 (all even at even indices): %s\n", result1 ? "PASS" : "FAIL");
    printf("Test 2 (odd at index 2): %s\n", result2 ? "PASS" : "FAIL");
    printf("Test 3 (odd at index 0): %s\n", result3 ? "PASS" : "FAIL");
    printf("Test 4 (empty array): %s\n", result4 ? "PASS" : "FAIL");
    printf("Test 5 (NULL pointer): %s\n", result5 ? "PASS" : "FAIL");
    
    return 0;
}