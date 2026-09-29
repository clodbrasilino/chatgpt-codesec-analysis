#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int addMinToEvenSum(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
    }
    if (sum % 2 == 0) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    int arr[] = {1, 3, 5, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int minAdd = addMinToEvenSum(arr, n);
    printf("Minimum number to add: %d\n", minAdd);
    return 0;
}