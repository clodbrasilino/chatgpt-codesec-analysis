#include <stdio.h>

long long binomialCoefficient(long long n, long long k) {
    long long res = 1;

    if (k > n - k) {
        k = n - k;
    }

    for (long long i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }

    return res;
} 

int main() {
    long long n, k;
    printf("Enter the values of n and k\n");
    if(scanf("%lld%lld", &n, &k) != 2) {
        printf("Invalid input\n");
        return 1;
    }
    if(n < 0 || k < 0) {
        printf("n and k can not be negative\n");
        return 1;
    }
    if(n < k) {
        printf("n can not be less than k\n");
        return 1;
    }
    long long res = binomialCoefficient(n, k);
    printf("The value of C(%lld, %lld) is %lld\n", n, k, res);

    return 0;
}