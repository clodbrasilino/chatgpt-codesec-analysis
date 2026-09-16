#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'numbers' can be declared as pointer to const [constParameterPointer]
 */
int sum_range(int *numbers, int start, int end) {
    if (numbers == NULL || start > end) {
        return 0;
    }
    int sum = 0;
    for (int i = start; i <= end; ++i) {
        sum += numbers[i];
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    /* Possible weaknesses found:
     *  Variable 'n' is assigned a value that is never used. [unreadVariable]
     */
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = sum_range(arr, 2, 5);
    printf("Sum: %d\n", result);
    return 0;
}