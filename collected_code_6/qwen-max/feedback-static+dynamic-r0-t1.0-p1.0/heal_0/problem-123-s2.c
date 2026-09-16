#include <stdio.h>

int sumOfProperDivisors(int n) {
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    return sum;
}

int isAmicable(int a, int b) {
    return sumOfProperDivisors(a) == b && sumOfProperDivisors(b) == a && a != b;
}

int sumAmicableNumbers(int max) {
    int sum = 0;
    for (int i = 1; i <= max; i++) {
        int dsum = sumOfProperDivisors(i);
        if (dsum > i && isAmicable(i, dsum)) {
            sum += i + dsum;
        }
    }
    return sum / 2;
}

int main() {
    int max = 10000;
    printf("Sum of all amicable numbers up to %d: %d\n", max, sumAmicableNumbers(max));
    return 0;
}