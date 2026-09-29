#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool isAbundant(int n) {
    int sum = 1; 
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            if (sum > INT_MAX - i) return false;
            sum += i;
            if (i != n / i && sum > INT_MAX - n / i) return false;
            sum += n / i;
        }
    }
    return (sum > n);
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (isAbundant(num)) {
        printf("%d is an abundant number.\n", num);
    } else {
        printf("%d is not an abundant number.\n", num);
    }

    return 0;
}