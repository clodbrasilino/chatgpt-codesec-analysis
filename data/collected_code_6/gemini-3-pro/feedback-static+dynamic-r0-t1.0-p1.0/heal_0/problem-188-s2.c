#include <stdio.h>
#include <stdbool.h>

bool canBeRepresentedByProductOfTwoSquares(long long n) {
    if (n < 0) {
        return false;
    }
    if (n == 0) {
        return true;
    }

    long long count = 0;
    while (n % 2 == 0) {
        count++;
        n /= 2;
    }
    if (count % 2 != 0) {
        return false;
    }

    for (long long i = 3; i * i <= n; i += 2) {
        count = 0;
        while (n % i == 0) {
            count++;
            n /= i;
        }
        if (count % 2 != 0) {
            return false;
        }
    }

    if (n > 2) {
        return false;
    }

    return true;
}

int main(void) {
    long long num;
    if (scanf("%lld", &num) != 1) {
        return 1;
    }

    if (canBeRepresentedByProductOfTwoSquares(num)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}