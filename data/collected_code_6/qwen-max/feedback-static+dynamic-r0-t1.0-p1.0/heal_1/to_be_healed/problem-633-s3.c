#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
long long sum_of_xor_pairs(int *array, int n) {
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            sum += (array[i] ^ array[j]);
        }
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    int *array = (int *)malloc(n * sizeof(int));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    printf("Enter the elements:\n");
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    long long result = sum_of_xor_pairs(array, n);
    printf("Sum of XOR of all pairs: %lld\n", result);

    free(array);
    return EXIT_SUCCESS;
}