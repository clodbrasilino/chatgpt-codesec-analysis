#include <stdio.h>

int countDivisors(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int num = 0;
    printf("Enter an integer: ");
    scanf("%d", &num);
    printf("Number of divisors: %d\n", countDivisors(num));
    return 0;
}