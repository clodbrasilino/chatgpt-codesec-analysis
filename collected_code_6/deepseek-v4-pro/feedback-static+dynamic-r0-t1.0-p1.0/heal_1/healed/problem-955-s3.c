#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_abundant(int num) {
    if (num < 1) {
        return false;
    }

    long long sum = 0;
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sum += i;
            if (sum > (long long)INT_MAX) {
                return true;
            }
        }
    }

    return sum > num;
}

int main(void) {
    int number;

    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (is_abundant(number)) {
        printf("%d is an abundant number\n", number);
    } else {
        printf("%d is not an abundant number\n", number);
    }

    return 0;
}