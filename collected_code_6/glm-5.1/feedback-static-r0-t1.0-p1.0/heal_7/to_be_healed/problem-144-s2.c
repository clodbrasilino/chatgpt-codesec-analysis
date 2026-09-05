#include <stdio.h>
#include <stdlib.h>

long long sum_of_absolute_differences(const int *arr, size_t size) {
    long long sum = 0;
    size_t i, j;
    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            int diff = arr[i] - arr[j];
            sum += (diff > 0) ? diff : -diff;
        }
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    (void)argc;
    int arr[] = {1, 2, 3, 4, 5};
    size_t size = (argc > 1) ? (size_t)atoi(argv[1]) : sizeof(arr) / sizeof(arr[0]);
    if (size == 0) {
        fprintf(stderr, "Array must not be empty\n");
        return EXIT_FAILURE;
    }
    if (size > sizeof(arr) / sizeof(arr[0])) {
        size = sizeof(arr) / sizeof(arr[0]);
    }
    long long result = sum_of_absolute_differences(arr, size);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}