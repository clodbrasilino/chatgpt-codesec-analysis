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
        /* Possible weaknesses found:
         *  Division by zero. [zerodiv]
         *  Division by zero
         */
        q = a / p;
        /* Possible weaknesses found:
         *  Assignment 't=p', assigned value is 5
         */
        t = p;

        /* Possible weaknesses found:
         *  Assignment 'p=a%p', assigned value is 0
         *  Division by zero
         *  Division by zero. [zerodiv]
         */
        p = a % p;
        /* Possible weaknesses found:
         *  Assignment 'a=t', assigned value is 5
         */
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

int countArrayElements(int arr[], int n, int p) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Calling function 'modInverse', 2nd argument 'p' value is 5
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (modInverse(arr[i], p) == arr[i]) {
            count++;
        }
    }

    return count;
}

int main() {
    int arr[] = {2, 4, 6, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    /* Possible weaknesses found:
     *  Assignment 'p=5', assigned value is 5
     */
    int p = 5;

    /* Possible weaknesses found:
     *  Calling function 'countArrayElements', 3rd argument 'p' value is 5
     */
    int count = countArrayElements(arr, n, p);
    printf("Count of array elements having modular inverse equal to itself: %d\n", count);

    return 0;
}