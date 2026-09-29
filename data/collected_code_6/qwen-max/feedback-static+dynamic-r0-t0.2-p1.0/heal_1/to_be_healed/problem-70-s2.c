#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'lengths' can be declared as pointer to const [constParameterPointer]
 *  expected 'int *' but argument is of type 'int **'
 */
int all_tuples_equal_length(int **tuples, int n, int *lengths) {
    if (n <= 0) return 1;
    for (int i = 1; i < n; ++i) {
        if (lengths[i] != lengths[0]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n = 5;
    /* Possible weaknesses found:
     *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
     *  (near initialization for 'lengths[4]')
     *  (near initialization for 'lengths[0]')
     *  (near initialization for 'lengths[1]')
     *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  (near initialization for 'lengths[3]')
     *  (near initialization for 'lengths[2]')
     */
    int *lengths[] = {3, 3, 3, 3, 3};
    int **tuples = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        /* Possible weaknesses found:
         *  invalid operands to binary * (have 'int *' and 'long unsigned int')
         *  invalid operands to binary expression ('int *' and 'unsigned long')
         */
        tuples[i] = (int *)malloc(lengths[i] * sizeof(int));
    }

    /* Possible weaknesses found:
     *  passing argument 3 of 'all_tuples_equal_length' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    if (all_tuples_equal_length(tuples, n, lengths)) {
        printf("All tuples have equal length.\n");
    } else {
        printf("Not all tuples have equal length.\n");
    }

    for (int i = 0; i < n; ++i) {
        free(tuples[i]);
    }
    free(tuples);

    return 0;
}