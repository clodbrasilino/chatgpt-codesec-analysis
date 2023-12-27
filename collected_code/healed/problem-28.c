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

int main() {
    int n = 0, k = 0;
    printf("Enter the values of n and k: ");
    scanf("%d%d", &n, &k);
    printf("The binomial coefficient C(%d, %d) is %d\n", n, k, binomialCoeff(n, k));
    return 0;
}