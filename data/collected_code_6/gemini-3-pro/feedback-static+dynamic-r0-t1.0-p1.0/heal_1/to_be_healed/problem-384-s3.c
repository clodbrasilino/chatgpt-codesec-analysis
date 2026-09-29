#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int findFrequencyOfSmallest(int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }

    int smallest = arr[0];
    int count = 1;

    for (size_t i = 1; i < size; ++i) {
        if (arr[i] < smallest) {
            smallest = arr[i];
            count = 1;
        } else if (arr[i] == smallest) {
            count++;
        }
    }

    return count;
}

int main() {
    int arr[] = {5, 2, 8, 2, 9, 2, 1, 1, 4, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int frequency = findFrequencyOfSmallest(arr, size);

    printf("Frequency of the smallest value: %d\n", frequency);

    return 0;
}