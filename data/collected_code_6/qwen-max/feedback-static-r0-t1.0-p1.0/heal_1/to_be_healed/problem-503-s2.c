#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'numbers' can be declared as pointer to const [constParameterPointer]
 */
int add_consecutive_numbers(int *numbers, int length) {
    if (length <= 0) {
        return -1;
    }
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += numbers[i];
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = add_consecutive_numbers(arr, n);
    if (result >= 0) {
        printf("Sum: %d\n", result);
    } else {
        printf("Error in adding numbers.\n");
    }
    return 0;
}