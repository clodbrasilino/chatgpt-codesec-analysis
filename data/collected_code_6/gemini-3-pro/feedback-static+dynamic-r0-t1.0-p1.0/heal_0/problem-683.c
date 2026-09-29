#include <stdio.h>
#include <stdbool.h>

bool sumOfTwoSquares(long long n) {
    if (n < 0) {
        return false;
    }
    for (long long i = 2; i * i <= n; i++) {
        int count = 0;
        if (n % i == 0) {
            while (n % i == 0) {
                count++;
                n /= i;
            }
            if (i % 4 == 3 && count % 2 != 0) {
                return false;
            }
        }
    }
    return n % 4 != 3;
}

int main() {
    long long num;

    if (scanf("%lld", &num) != 1) {
        return 1;
    }

    if (sumOfTwoSquares(num)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}