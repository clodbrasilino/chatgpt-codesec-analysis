#include <stdio.h>

void findTriplet(int arr[], int n, int targetSum) {
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'arr[k]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                if (arr[i] + arr[j] + arr[k] == targetSum) {
                    /* Possible weaknesses found:
                     *  Cannot determine that 'arr[k]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                     *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                     *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                     */
                    printf("%d, %d, %d\n", arr[i], arr[j], arr[k]);
                }
            }
        }
    }
}

int main() {
    int n, targetSum;
    printf("Enter the size of the array: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter the target sum: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'targetSum' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &targetSum);

    printf("Triplets with sum %d are:\n", targetSum);
    findTriplet(arr, n, targetSum);

    return 0;
}