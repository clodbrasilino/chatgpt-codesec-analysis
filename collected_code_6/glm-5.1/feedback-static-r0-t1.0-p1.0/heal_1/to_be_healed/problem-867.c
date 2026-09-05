#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int min_add_to_even(int *arr, size_t size) {
    if (size == 0) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += arr[i];
    }

    if (sum % 2 == 0) {
        return 0;
    }

    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    size_t size = (size_t)(argc - 1);
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        return 1;
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
            free(arr);
            return 1;
        }
        arr[i] = (int)val;
    }

    int result = min_add_to_even(arr, size);

    printf("%d\n", result);

    free(arr);

    return 0;
}