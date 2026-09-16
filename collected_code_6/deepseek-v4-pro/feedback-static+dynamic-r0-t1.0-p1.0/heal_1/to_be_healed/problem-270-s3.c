#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int sum_even_at_even_positions(int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return 0;
    }

    int sum = 0;
    for (int i = 0; i < size; i += 2) {
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }
    return sum;
}

int main(void) {
    int arr[] = {2, 5, 4, 7, 8, 9, 10, 11, 12};
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = sum_even_at_even_positions(arr, size);
    printf("Sum: %d\n", result);

    return 0;
}