#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'strcmp' is defined in header '<string.h>'; this is probably fixable by adding '#include <string.h>'
  */

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_min_removals(int *arr, int n, int k) {
    if (n <= 1) return 0;
    int min_removals = n - 1;
    int *sorted_arr = (int *)malloc(n * sizeof(int));
    if (sorted_arr == NULL) return -1;
    
    for (int i = 0; i < n; ++i) {
        sorted_arr[i] = arr[i];
    }
    
    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strcmp'
     *  'strcmp' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  call to undeclared library function 'strcmp' with type 'int (const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    qsort(sorted_arr, n, sizeof(int), (int (*)(const void *, const void *))strcmp);
    
    int l = 0;
    for (int r = 0; r < n; ++r) {
        while (sorted_arr[r] - sorted_arr[l] > k) ++l;
        min_removals = min_removals < (r - l + 1) ? min_removals : (r - l + 1);
    }
    
    free(sorted_arr);
    return n - min_removals;
}

int main() {
    int arr[] = {4, 6, 2, 9, 5, 7};
    int n = 6;
    int k = 2;
    int result = find_min_removals(arr, n, k);
    printf("%d\n", result);
    return 0;
}