#include<stdio.h>

int gcd(int a, int b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int findlcm(int arr[], int n) {
    int i, lcm = arr[0];
    for (i = 1; i < n; i++)
        lcm = (arr[i] * lcm) / gcd(arr[i], lcm);
    return lcm;
}

int main() {
    int arr[] = {2, 7, 3, 9, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("LCM of array elements is %d ", findlcm(arr, n));
    return 0;
}