#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
void findFirstEvenOddSum(int *arr, size_t size, int *sum) {
    if (arr == NULL || sum == NULL) {
        return;
    }

    int first_even = 0;
    int first_odd = 0;
    int found_even = 0;
    int found_odd = 0;

    for (size_t i = 0; i < size; i++) {
        if (!found_even && arr[i] % 2 == 0) {
            first_even = arr[i];
            found_even = 1;
        }
        if (!found_odd && arr[i] % 2 != 0) {
            first_odd = arr[i];
            found_odd = 1;
        }
        if (found_even && found_odd) {
            break;
        }
    }

    *sum = 0;
    if (found_even) {
        *sum += first_even;
    }
    if (found_odd) {
        *sum += first_odd;
    }
}

int main(void) {
    int arr[] = {3, 7, 2, 8, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int sum = 0;

    findFirstEvenOddSum(arr, size, &sum);

    printf("%d\n", sum);

    return 0;
}