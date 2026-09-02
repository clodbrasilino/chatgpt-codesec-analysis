#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

int sum_of_divisors(int n) {
    int i, sum = 0;
    for (i = 1; i <= n; i++) {
        if (n % i == 0)
            sum += i;
    }
    return sum;
}

int common_divisors_sum(int x, int y) {
    int divisor_gcd = gcd(x, y);
    return sum_of_divisors(divisor_gcd);
}

int main() {
    int a = 0, b = 0;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    if (a > 0 && b > 0) {
        int result = common_divisors_sum(a, b);
        printf("Sum of common divisors of %d and %d is %d\n", a, b, result);
    } else {
        printf("Please enter positive integers.\n");
    }

    return 0;
}