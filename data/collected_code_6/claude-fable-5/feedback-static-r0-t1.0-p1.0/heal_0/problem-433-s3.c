#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 5

int is_greater_than_all(int number, const int *arr, size_t size)
{
    size_t i;

    if (arr == NULL || size == 0U) {
        return 0;
    }

    for (i = 0U; i < size; i++) {
        if (number <= arr[i]) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    int arr[ARRAY_SIZE];
    int number;
    size_t i;

    printf("Enter %d array elements:\n", ARRAY_SIZE);
    for (i = 0U; i < ARRAY_SIZE; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Error: invalid input for array element.\n");
            return EXIT_FAILURE;
        }
    }

    printf("Enter the number to check: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Error: invalid input for number.\n");
        return EXIT_FAILURE;
    }

    if (is_greater_than_all(number, arr, ARRAY_SIZE) == 1) {
        printf("%d is greater than all elements of the array.\n", number);
    } else {
        printf("%d is not greater than all elements of the array.\n", number);
    }

    return EXIT_SUCCESS;
}