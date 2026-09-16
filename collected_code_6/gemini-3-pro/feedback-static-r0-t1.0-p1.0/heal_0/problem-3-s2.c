#include <stdio.h>
#include <stdbool.h>

bool is_non_prime(int n) {
    if (n <= 1) {
        return true;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return true;
        }
    }
    return false;
}

int main(void) {
    int num;
    
    if (scanf("%d", &num) != 1) {
        return 1;
    }

    if (is_non_prime(num)) {
        printf("%d is a non-prime number.\n", num);
    } else {
        printf("%d is a prime number.\n", num);
    }

    return 0;
}