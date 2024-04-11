#include <stdio.h>

int binomialCoeff(int n, int k) {
    int res = 1;
    if (k > n - k)
        k = n - k;
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

int countSequences(int n) {
    int count = 0;
    for (int i = 0; i <= n; ++i)
        count += binomialCoeff(n, i) * binomialCoeff(n, i);
    return count;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("Count of all binary sequences of length %d such that sum of first %d bits is same as sum of last %d bits is %d\n", 2*n, n, n, countSequences(n));
    return 0;
}