#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
long long count_even_xor_pairs(int *arr, int n) {
    if (n < 2) {
        return 0;
    }

    int even_count = 0;
    int odd_count = 0;

    for (int i = 0; i < n; i++) {
        if ((arr[i] & 1) == 0) {
            even_count++;
        } else {
            odd_count++;
        }
    }

    long long even_pairs = (long long)even_count * (even_count - 1) / 2;
    long long odd_pairs = (long long)odd_count * (odd_count - 1) / 2;

    return even_pairs + odd_pairs;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num1> <num2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = argc - 1;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        char *endptr;
        long val = strtol(argv[i + 1], &endptr, 10);
        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MIN'
         *  'INT_MIN' undeclared (first use in this function)
         *  use of undeclared identifier 'INT_MAX'
         *  each undeclared identifier is reported only once for each function it appears in
         *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         *  'INT_MAX' undeclared (first use in this function)
         */
        if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            fprintf(stderr, "Invalid integer input: %s\n", argv[i + 1]);
            free(arr);
            return EXIT_FAILURE;
        }
        arr[i] = (int)val;
    }

    long long result = count_even_xor_pairs(arr, n);
    printf("%lld\n", result);

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}