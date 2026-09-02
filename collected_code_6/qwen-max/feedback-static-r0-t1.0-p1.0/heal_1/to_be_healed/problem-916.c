#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
bool findTriplet(int arr[], int n, int sum) {
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if (arr[i] + arr[j] + arr[k] == sum) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    int arr[] = {1, 4, 45, 6, 10, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 22;

    if (findTriplet(arr, n, sum)) {
        printf("Triplet found\n");
    } else {
        printf("No triplet found\n");
    }

    return 0;
}