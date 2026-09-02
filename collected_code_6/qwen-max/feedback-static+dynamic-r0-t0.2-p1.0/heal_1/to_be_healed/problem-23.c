#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'sizes' can be declared as pointer to const [constParameterPointer]
 */
int max_sum_list(int **lists, int *sizes, int n) {
    if (n == 0) return 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'current_sum' can be reduced. [variableScope]
     */
    int max_sum = 0, current_sum;
    for (int i = 0; i < n; ++i) {
        current_sum = 0;
        for (int j = 0; j < sizes[i]; ++j) {
            /* Possible weaknesses found:
             * ASan: SEGV
             * UBSan: load of misaligned address 0x000200000001 for type 'int', which requires 4 byte alignment
             */
            current_sum += lists[i][j];
        }
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }
    return max_sum;
}

int main() {
    int n = 4;
    int *sizes = (int[]){3, 2, 4, 1};
    int **lists = (int**){
        /* Possible weaknesses found:
         *  (near initialization for '(anonymous)')
         *  initialization of 'int **' from incompatible pointer type 'int *' [-Wincompatible-pointer-types]
         */
        (int[]){1, 2, 3},
        (int[]){4, 5},
        (int[]){6, 7, 8, 9},
        (int[]){10}
    };

    int result = max_sum_list(lists, sizes, n);
    printf("The maximum sum is: %d\n", result);

    return 0;
}