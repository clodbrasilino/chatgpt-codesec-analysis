#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
double positive_ratio(int *arr, int n) {
    if (n <= 0) return 0.0;
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > 0) {
            ++count;
        }
    }
    return (double)count / n;
}

int main() {
    int arr[] = {1, -2, 3, -4, 5, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Positive ratio: %.2f\n", positive_ratio(arr, n));
    return 0;
}