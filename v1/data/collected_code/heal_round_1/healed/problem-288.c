#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int modInverse(int a, int p) {
    int m0 = p, t, q;
    int x0 = 0, x1 = 1;

    if (p == 1)
        return 0;

    while (a > 1) {
        if (p == 0)
            return -1;

        q = a / p;
        t = p;
        p = a % p;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

int countArrayElements(const int arr[], int n, int p) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (modInverse(arr[i], p) == arr[i]) {
            count++;
        }
    }

    return count;
}

int main() {
    int arr[] = {2, 4, 6, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int p = 5;

    int count = countArrayElements(arr, n, p);
    printf("Count of array elements having modular inverse equal to itself: %d\n", count);

    return 0;
}