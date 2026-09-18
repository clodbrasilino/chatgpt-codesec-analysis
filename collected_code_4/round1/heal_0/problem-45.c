#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

int findGcd(int arr[], int n) {
    int result = arr[0];
    for (int i = 1; i < n; i++) {
        result = gcd(result, arr[i]);
        if(result == 1) {
           return 1;
        }
    }
    return result;
}

int main() {
    int n = 5;
    int arr[] = {2, 3, 4, 5, 6};
    printf("The GCD of the array elements is: %d\n", findGcd(arr, n));
    return 0;
}