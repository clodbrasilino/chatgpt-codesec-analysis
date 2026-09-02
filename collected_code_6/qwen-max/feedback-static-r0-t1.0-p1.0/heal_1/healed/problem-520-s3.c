#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

int find_lcm_of_array(const int *arr, int n) {
    int result = arr[0];
    for (int i = 1; i < n; i++) {
        result = lcm(result, arr[i]);
    }
    return result;
}

int main() {
    const int arr[] = {2, 7, 3, 9, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("LCM of array elements is %d\n", find_lcm_of_array(arr, n));
    return 0;
}