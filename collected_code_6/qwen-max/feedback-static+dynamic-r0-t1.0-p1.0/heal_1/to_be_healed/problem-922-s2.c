#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
void find_max_product_pair(int arr[], int n, int *max1, int *max2) {
    if (n < 2) return;

    *max1 = INT_MIN;
    *max2 = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (arr[i] > *max1) {
            *max2 = *max1;
            *max1 = arr[i];
        } else if (arr[i] > *max2) {
            *max2 = arr[i];
        }
    }
}

int main() {
    int arr[] = {1, 4, 3, 6, 7, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max1, max2;

    find_max_product_pair(arr, n, &max1, &max2);

    if (max2 != INT_MIN)
        printf("The pair with the highest product is: %d, %d\n", max1, max2);
    else
        printf("Array does not have at least two elements.\n");

    return 0;
}