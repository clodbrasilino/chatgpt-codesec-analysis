#include <stdio.h>
#include <stdbool.h>

bool isAbundant(int n) {
    if (n <= 0) {
        return false;
    }

    int sum = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }

    return sum > n;
}

int main(void) {
    int num;
    
    if (scanf("%d", &num) != 1) {
        return 1;
    }

    if (isAbundant(num)) {
        printf("%d is an abundant number.\n", num);
    } else {
        printf("%d is not an abundant number.\n", num);
    }

    return 0;
}