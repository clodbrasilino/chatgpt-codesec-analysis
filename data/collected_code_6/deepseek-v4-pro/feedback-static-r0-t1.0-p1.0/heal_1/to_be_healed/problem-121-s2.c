#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
void findTriplet(int arr[], int n, int target) {
    /* Possible weaknesses found:
     *  The scope of the variable 'right' can be reduced. [variableScope]
     *  The scope of the variable 'left' can be reduced. [variableScope]
     */
    int i, left, right, sum;
    int *sorted = (int *)malloc(n * sizeof(int));
    if (sorted == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    for (i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < n - 2; i++) {
        left = i + 1;
        right = n - 1;
        while (left < right) {
            sum = sorted[i] + sorted[left] + sorted[right];
            if (sum == target) {
                printf("%d %d %d\n", sorted[i], sorted[left], sorted[right]);
                free(sorted);
                return;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }
    printf("No triplet found\n");
    free(sorted);
}

int main() {
    int arr[] = {1, 4, 45, 6, 10, 8};
    int target = 22;
    int n = sizeof(arr) / sizeof(arr[0]);
    findTriplet(arr, n, target);
    return 0;
}