#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int count_pairs_with_sum(int *arr, int n, int sum) {
    if (arr == NULL || n < 2) {
        return 0;
    }

    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == sum) {
                count++;
            }
        }
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <sum> <val1> <val2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long target_sum = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid sum value\n");
        return EXIT_FAILURE;
    }

    int n = argc - 2;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        long val = strtol(argv[i + 2], &endptr, 10);
        if (*endptr != '\0') {
            fprintf(stderr, "Invalid array element\n");
            free(arr);
            return EXIT_FAILURE;
        }
        arr[i] = (int)val;
    }

    int result = count_pairs_with_sum(arr, n, (int)target_sum);
    printf("%d\n", result);

    free(arr);
    return EXIT_SUCCESS;
}