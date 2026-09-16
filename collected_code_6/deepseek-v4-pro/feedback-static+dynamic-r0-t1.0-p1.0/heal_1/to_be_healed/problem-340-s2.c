#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int sum_three_lowest_positive(int arr[], int size) {
    int first = INT_MAX, second = INT_MAX, third = INT_MAX;
    bool found_first = false, found_second = false, found_third = false;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] <= 0) {
            continue;
        }
        
        if (arr[i] < first) {
            third = second;
            found_third = found_second;
            second = first;
            found_second = found_first;
            first = arr[i];
            found_first = true;
        } else if (arr[i] < second || !found_second) {
            third = second;
            found_third = found_second;
            second = arr[i];
            found_second = true;
        } else if (arr[i] < third || !found_third) {
            third = arr[i];
            found_third = true;
        }
    }
    
    if (!found_first || !found_second || !found_third) {
        return 0;
    }
    
    return first + second + third;
}

int main(void) {
    int test1[] = {5, 9, 1, 3, 7, -4, 2};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    printf("Sum: %d\n", sum_three_lowest_positive(test1, size1));
    
    int test2[] = {-1, -2, -3};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    printf("Sum: %d\n", sum_three_lowest_positive(test2, size2));
    
    int test3[] = {10, 20, 30, 40, 50};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    printf("Sum: %d\n", sum_three_lowest_positive(test3, size3));
    
    int test4[] = {4, 1, 3, 2};
    int size4 = sizeof(test4) / sizeof(test4[0]);
    printf("Sum: %d\n", sum_three_lowest_positive(test4, size4));
    
    return 0;
}