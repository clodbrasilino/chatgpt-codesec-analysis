#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void findThreeClosest(int *arr1, int size1, int *arr2, int size2, int *arr3, int size3) {
    int i = 0, j = 0, k = 0;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' undeclared (first use in this function)
     */
    int min_diff = INT_MAX;
    int res_i, res_j, res_k;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (i < size1 && j < size2 && k < size3) {
        int max_val = (arr1[i] > arr2[j]) ? ((arr1[i] > arr3[k]) ? arr1[i] : arr3[k]) : ((arr2[j] > arr3[k]) ? arr2[j] : arr3[k]);
        int min_val = (arr1[i] < arr2[j]) ? ((arr1[i] < arr3[k]) ? arr1[i] : arr3[k]) : ((arr2[j] < arr3[k]) ? arr2[j] : arr3[k]);

        if (max_val - min_val < min_diff) {
            min_diff = max_val - min_val;
            res_i = i;
            res_j = j;
            res_k = k;
        }

        if (arr1[i] == min_val) i++;
        else if (arr2[j] == min_val) j++;
        else k++;
    }

    /* Possible weaknesses found:
     *  Uninitialized variable: res_i
     *  Uninitialized variable: res_i [uninitvar]
     *  Uninitialized variable: res_j
     *  Uninitialized variable: res_j [uninitvar]
     *  Uninitialized variable: res_k
     *  Uninitialized variable: res_k [uninitvar]
     */
    printf("The three closest elements are: %d, %d, %d\n", arr1[res_i], arr2[res_j], arr3[res_k]);
}

int main() {
    int arr1[] = {1, 4, 10};
    int arr2[] = {2, 15, 20};
    int arr3[] = {10, 12};

    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int size3 = sizeof(arr3) / sizeof(arr3[0]);

    findThreeClosest(arr1, size1, arr2, size2, arr3, size3);

    return 0;
}