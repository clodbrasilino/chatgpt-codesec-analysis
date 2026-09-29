#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int count_unequal_pairs(const int *arr, size_t size) {
    if (arr == NULL || size < 2) {
        return 0;
    }
    
    int count = 0;
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (arr[i] != arr[j]) {
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
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num1> <num2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t size = (size_t)(argc - 1);
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
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
            fprintf(stderr, "Invalid integer argument: %s\n", argv[i + 1]);
            free(arr);
            return EXIT_FAILURE;
        }
        arr[i] = (int)val;
    }

    int result = count_unequal_pairs(arr, size);
    printf("%d\n", result);

    free(arr);
    return EXIT_SUCCESS;
}