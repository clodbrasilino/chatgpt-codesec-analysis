#include <stdio.h>
#include <stdbool.h>

bool is_abundant(int num) {
    if (num < 1) {
        return false;
    }

    int sum = 0;
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sum += i;
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