#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int frequency_of_smallest(int arr[], int size) {
    if (size <= 0) {
        return 0;
    }

    int min = arr[0];
    int count = 1;

    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
            count = 1;
        } else if (arr[i] == min) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int arr[] = {5, 2, 2, 8, 2, 9, 2};
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = frequency_of_smallest(arr, size);

    printf("%d\n", result);

    return 0;
}