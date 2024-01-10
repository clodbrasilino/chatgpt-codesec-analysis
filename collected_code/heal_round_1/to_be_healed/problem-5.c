#include<stdio.h>

int countWays(int n) {
    int A[n+1];
    A[0] = 1;
    A[1] = 0;
    A[2] = 3;
    /* Possible weaknesses found:
     *  Assignment 'i=3', assigned value is 3
     */
    for (int i = 3; i <= n; i++) {
        /* Possible weaknesses found:
         *  stack-based buffer under-read [CWE-127] [-Wanalyzer-out-of-bounds]
         *  use of uninitialized value '*A[<unknown>]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  Negative array index
         *  Array 'A[2147483648]' accessed at index -1, which is out of bounds. [negativeIndex]
         */
        A[i] = A[i-2] * 4 - A[i-4];
    }
    return A[n];
}

int main() {
    int n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    printf("Number of ways to fill the board: %d", countWays(n));
    return 0;
}