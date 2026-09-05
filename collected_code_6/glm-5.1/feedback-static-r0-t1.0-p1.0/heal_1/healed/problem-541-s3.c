#include <stdio.h>

int is_abundant(int num) {
    if (num <= 0) {
        return 0;
    }
    int sum = 0;
    for (int i = 1; i <= num / 2; ++i) {
        if (num % i == 0) {
            sum += i;
        }
    }
    return sum > num;
}

int main(void) {
    if (scanf("%d", &(int){0}) != 1) {
        return 1;
    }
    int number;
    if (scanf("%d", &number) != 1) {
        return 1;
    }
    if (number <= 0) {
        return 1;
    }
    if (is_abundant(number)) {
        printf("%d is an abundant number.\n", number);
    } else {
        printf("%d is not an abundant number.\n", number);
    }
    return 0;
}