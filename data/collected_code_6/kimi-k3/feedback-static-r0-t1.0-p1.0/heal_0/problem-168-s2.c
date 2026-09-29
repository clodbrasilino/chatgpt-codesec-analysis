#include <stdio.h>
#include <stdlib.h>

int findFrequency(int arr[], int size, int num) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == num) {
            count++;
        }
    }
    return count;
}

int main() {
    int size, num;

    printf("Enter the size of the array: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        fprintf(stderr, "Invalid input for array size.\n");
        return EXIT_FAILURE;
    }

    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input for array element.\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }

    printf("Enter the number to find its frequency: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input for the number.\n");
        free(arr);
        return EXIT_FAILURE;
    }

    int frequency = findFrequency(arr, size, num);
    printf("Frequency of %d is %d\n", num, frequency);

    free(arr);
    return EXIT_SUCCESS;
}