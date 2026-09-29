#include <stdio.h>
#include <stdbool.h>

bool is_even_divisor_count(int n) {
    int count = 0;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            if (i * i == n)
                count += 1;
            else
                count += 2;
        }
    }
    return count % 2 == 0;
}

int main() {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (is_even_divisor_count(num)) {
        printf("The count of divisors is even.\n");
    } else {
        printf("The count of divisors is odd.\n");
    }

    return 0;
}