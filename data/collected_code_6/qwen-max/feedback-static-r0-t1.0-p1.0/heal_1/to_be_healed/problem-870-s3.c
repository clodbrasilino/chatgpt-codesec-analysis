#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int sum_positive(int *arr, size_t len) {
    int sum = 0;
    for(size_t i = 0; i < len; ++i) {
        if(arr[i] > 0) {
            sum += arr[i];
        }
    }
    return sum;
}

int main() {
    int numbers[] = {1, -2, 3, -4, 5, 6};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    int result = sum_positive(numbers, length);
    printf("Sum of positive numbers: %d\n", result);
    return 0;
}