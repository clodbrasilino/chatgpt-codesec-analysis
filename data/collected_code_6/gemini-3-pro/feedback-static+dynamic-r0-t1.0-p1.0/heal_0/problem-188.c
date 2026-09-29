#include <stdio.h>
#include <stdbool.h>

bool canBeRepresentedByProductOfTwoSquares(long long n) {
    if (n < 0) {
        return false;
    }
    if (n == 0) {
        return true;
    }

    long long i = 2;
    while (i * i <= n) {
        int count = 0;
        while (n % i == 0) {
            count++;
            n /= i;
        }
        if (count % 2 != 0) {
            return false;
        }
        i++;
    }

    if (n > 1) {
        return false;
    }

    return true;
}

int main(void) {
    long long num = 0;
    
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