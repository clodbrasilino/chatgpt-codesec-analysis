#include <stdio.h>

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long findSmallestMultiple(int n) {
    long long ans = 1;
    for (int i = 1; i <= n; i++)
        ans = (ans * i)/(gcd(ans, i));
    return ans;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The smallest multiple of first %d numbers is %lld\n", n, findSmallestMultiple(n));
    return 0;
}