#include <stdio.h>
#include <stdlib.h>

unsigned long long sumOfFifthPowers(int n) {
    if (n < 0) {
        return 0;
    }

    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long i_ll = (unsigned long long)i;
        sum += i_ll * i_ll * i_ll * i_ll * i_ll;
    }
    
    return sum;
}

int main() {
    int n;

    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (n < 0) {
        return 1;
    }

    unsigned long long result = sumOfFifthPowers(n);
    printf("%llu\n", result);

    return 0;
}