#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'numbers' can be declared as pointer to const [constParameterPointer]
 */
int sum_negative(int *numbers, int length) {
    int sum = 0;
    for (int i = 0; i < length; ++i) {
        if (numbers[i] < 0) {
            sum += numbers[i];
        }
    }
    return sum;
}

int main() {
    int arr[] = {1, -2, 3, -4, 5, -6};
    int length = sizeof(arr) / sizeof(arr[0]);
    int result = sum_negative(arr, length);
    printf("Sum of negative numbers: %d\n", result);
    return 0;
}