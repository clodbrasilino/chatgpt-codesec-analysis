#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int find_odd_occurrence(int *array, size_t size) {
    int result = 0;
    for (size_t i = 0; i < size; i++) {
        result ^= array[i];
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <numbers...>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t size = argc - 1;
    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        long val = strtol(argv[i + 1], NULL, 10);
        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MIN'
         *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         *  'INT_MIN' undeclared (first use in this function)
         *  use of undeclared identifier 'INT_MAX'
         *  each undeclared identifier is reported only once for each function it appears in
         *  'INT_MAX' undeclared (first use in this function)
         */
        if (val > INT_MAX || val < INT_MIN) {
            fprintf(stderr, "Integer overflow for argument %s\n", argv[i + 1]);
            free(array);
            return EXIT_FAILURE;
        }
        array[i] = (int)val;
    }

    int odd_occurrence = find_odd_occurrence(array, size);
    printf("%d\n", odd_occurrence);

    free(array);
    return EXIT_SUCCESS;
}