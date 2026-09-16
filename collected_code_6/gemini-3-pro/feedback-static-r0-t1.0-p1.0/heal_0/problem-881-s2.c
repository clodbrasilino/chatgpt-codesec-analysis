#include <stdio.h>
#include <stdlib.h>

void find_first_even_odd_sum(const int *arr, size_t size, int *sum, int *found) {
    if (arr == NULL || sum == NULL || found == NULL) {
        return;
    }

    int first_even = 0;
    int first_odd = 0;
    int even_found = 0;
    int odd_found = 0;

    for (size_t i = 0; i < size; ++i) {
        if (!even_found && arr[i] % 2 == 0) {
            first_even = arr[i];
            even_found = 1;
        } else if (!odd_found && arr[i] % 2 != 0) {
            first_odd = arr[i];
            odd_found = 1;
        }

        if (even_found && odd_found) {
            break;
        }
    }

    if (even_found && odd_found) {
        *sum = first_even + first_odd;
        *found = 1;
    } else {
        *found = 0;
    }
}

int main(void) {
    int arr[] = {3, 5, 8, 11, 14};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int sum = 0;
    int found = 0;

    find_first_even_odd_sum(arr, size, &sum, &found);

    if (found) {
        printf("Sum of first even and odd number: %d\n", sum);
    } else {
        printf("Could not find both an even and an odd number in the list.\n");
    }

    return 0;
}