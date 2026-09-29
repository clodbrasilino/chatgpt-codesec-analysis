#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool check_even_indices_even_values(const int *arr, size_t size)
{
    if (arr == NULL || size == 0)
    {
        return true;
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
    const int test1[] = {2, 5, 4, 7, 6, 9, 8};
    const int test2[] = {2, 5, 3, 7, 6};
    const int test3[] = {1, 2, 3};
    const int *test4 = NULL;
    const int *test5 = NULL;
    
    bool result1 = check_even_indices_even_values(test1, sizeof(test1) / sizeof(test1[0]));
    bool result2 = check_even_indices_even_values(test2, sizeof(test2) / sizeof(test2[0]));
    bool result3 = check_even_indices_even_values(test3, sizeof(test3) / sizeof(test3[0]));
    /* Possible weaknesses found:
     *  Calling function 'check_even_indices_even_values' returns 1
     *  Assignment 'result4=check_even_indices_even_values(test4,0)', assigned value is 1
     */
    bool result4 = check_even_indices_even_values(test4, 0);
    /* Possible weaknesses found:
     *  Assignment 'result5=check_even_indices_even_values(test5,5)', assigned value is 1
     *  Calling function 'check_even_indices_even_values' returns 1
     */
    bool result5 = check_even_indices_even_values(test5, 5);
    
    printf("Test 1 (all even at even indices): %s\n", result1 ? "PASS" : "FAIL");
    printf("Test 2 (odd at index 2): %s\n", result2 ? "PASS" : "FAIL");
    printf("Test 3 (odd at index 0): %s\n", result3 ? "PASS" : "FAIL");
    /* Possible weaknesses found:
     *  Condition 'result4' is always true
     *  Condition 'result4' is always true [knownConditionTrueFalse]
     */
    printf("Test 4 (empty array): %s\n", result4 ? "PASS" : "FAIL");
    /* Possible weaknesses found:
     *  Condition 'result5' is always true [knownConditionTrueFalse]
     *  Condition 'result5' is always true
     */
    printf("Test 5 (NULL pointer): %s\n", result5 ? "PASS" : "FAIL");
    
    return 0;
}