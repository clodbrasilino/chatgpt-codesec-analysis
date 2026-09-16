#include <stdio.h>
#include <stdlib.h>

int find_first_even_odd_division(const int *arr, size_t size, double *result) {
    if (arr == NULL || result == NULL) {
        return -1;
    }

    int first_even = 0;
    int first_odd = 0;
    int found_even = 0;
    int found_odd = 0;

    for (size_t i = 0; i < size; ++i) {
        if (!found_even && arr[i] % 2 == 0) {
            first_even = arr[i];
            found_even = 1;
        } else if (!found_odd && arr[i] % 2 != 0) {
            first_odd = arr[i];
            found_odd = 1;
        }

        if (found_even && found_odd) {
            break;
        }
    }

    if (!found_even || !found_odd) {
        return -1; 
    }

    if (first_odd == 0) {
        return -2; 
    }

    *result = (double)first_even / (double)first_odd;
    return 0;
}

int main(void) {
    int numbers[] = {3, 7, 8, 11, 4, 2};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    double division_result = 0.0;

    int status = find_first_even_odd_division(numbers, size, &division_result);

    if (status == 0) {
        printf("Result: %.2f\n", division_result);
    } else if (status == -1) {
        printf("Error: Could not find both an even and an odd number.\n");
    } else if (status == -2) {
        printf("Error: Division by zero (first odd number is 0).\n");
    } else {
        printf("Unknown error occurred.\n");
    }

    return EXIT_SUCCESS;
}