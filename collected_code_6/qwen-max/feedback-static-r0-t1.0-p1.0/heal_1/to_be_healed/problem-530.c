#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
double find_ratio_of_negatives(int arr[], int n) {
    if (n <= 0) return 0.0;

    int negative_count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            negative_count++;
        }
    }

    return (double)negative_count / n;
}

int main() {
    int arr[] = {1, -2, 3, -4, 5, -6};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    double ratio = find_ratio_of_negatives(arr, n);
    printf("Ratio of negative numbers: %.2f\n", ratio);

    return 0;
}