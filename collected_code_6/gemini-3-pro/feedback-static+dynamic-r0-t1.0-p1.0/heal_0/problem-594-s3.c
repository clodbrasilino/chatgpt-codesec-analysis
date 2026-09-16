#include <stdio.h>
#include <stdlib.h>

int find_difference(const int *arr, size_t size, int *error) {
    if (arr == NULL || error == NULL) {
        if (error != NULL) {
            *error = 1;
        }
        return 0;
    }

    int first_even = 0;
    int first_odd = 0;
    int found_even = 0;
    int found_odd = 0;

    for (size_t i = 0; i < size; ++i) {
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

    if (!found_even || !found_odd) {
        *error = 1;
        return 0;
    }

    *error = 0;
    return first_even - first_odd;
}

int main(void) {
    int arr[] = {3, 5, 4, 8, 7};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int error = 0;
    
    int difference = find_difference(arr, size, &error);
    
    if (error == 0) {
        printf("%d\n", difference);
    } else {
        printf("Error: Could not find both an even and an odd number in the given list.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}