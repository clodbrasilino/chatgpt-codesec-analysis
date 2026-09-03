#include <stdio.h>

int maxSumNoThreeConsecutive(const int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    if (n == 1) {
        return arr[0] > 0 ? arr[0] : 0;
    }

    int prev3 = 0;
    int prev2 = arr[0] > 0 ? arr[0] : 0;

    int val1 = prev2;
    int val2 = arr[1];
    int val3 = arr[0] + arr[1];
    int prev1 = val1;

    if (val2 > prev1) {
        prev1 = val2;
    }
    if (val3 > prev1) {
        prev1 = val3;
    }

    if (n == 2) {
        return prev1;
    }

    for (int i = 3; i <= n; ++i) {
        int valA = prev1;
        int valB = arr[i - 1] + prev2;
        int valC = arr[i - 1] + arr[i - 2] + prev3;

        int curr = valA;
        if (valB > curr) {
            curr = valB;
        }
        if (valC > curr) {
            curr = valC;
        }

        prev3 = prev2;
        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    printf("%d\n", maxSumNoThreeConsecutive(arr, n));
    return 0;
}