#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_largest_positive(int *arr, int n) {
    int max = INT_MIN;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > 0 && arr[i] > max) {
            max = arr[i];
        }
    }
    return max == INT_MIN ? -1 : max;
}

int main() {
    int arr[] = {3, -1, 7, 2, -5, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int largest = find_largest_positive(arr, n);
    if (largest != -1) {
        printf("The largest positive number is: %d\n", largest);
    } else {
        printf("No positive numbers found.\n");
    }
    return 0;
}