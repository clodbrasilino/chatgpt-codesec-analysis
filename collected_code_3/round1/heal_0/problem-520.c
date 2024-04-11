#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int findlcm(int arr[], int n) {
    int ans = arr[0];
    for (int i = 1; i < n; i++)
        ans = (((arr[i] * ans)) /
                (gcd(arr[i], ans)));

    return ans;
}

int main() {
    int arr[] = {2, 7, 3, 9, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d", findlcm(arr, n));
    return 0;
}