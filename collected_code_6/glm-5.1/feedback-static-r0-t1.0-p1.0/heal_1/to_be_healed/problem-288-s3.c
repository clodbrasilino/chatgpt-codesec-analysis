#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int count_modular_inverse_self(int *arr, int n, int p) {
    int count = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'val' can be reduced. [variableScope]
     */
    long long val;
    for (int i = 0; i < n; i++) {
        val = arr[i];
        if (val <= 0 || val >= p) {
            continue;
        }
        long long sq = (val * val) % p;
        if (sq == 1) {
            count++;
        }
    }
    return count;
}

int main() {
    /* Possible weaknesses found:
     *  'p' undeclared (first use in this function)
     *  use of undeclared identifier 'p'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    int arr[] = {1, 2, 3, 4, 5, 6, p - 1};
    /* Possible weaknesses found:
     *  invalid application of 'sizeof' to an incomplete type 'int[]'
     */
    int n = sizeof(arr) / sizeof(arr[0]);
    int p = 7;
    int result = count_modular_inverse_self(arr, n, p);
    printf("%d\n", result);
    return 0;
}