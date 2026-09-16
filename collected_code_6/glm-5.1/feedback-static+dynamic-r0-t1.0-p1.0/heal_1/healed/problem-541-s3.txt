#include <stdio.h>

int is_abundant(int num) {
    if (num <= 0) {
        return 0;
    }
    int sum = 1;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            sum += i;
            if (i * i != num) {
                sum += num / i;
            }
        }
    }
    return sum > num;
}

int main(void) {
    int number = 12;
    if (is_abundant(number)) {
        printf("%d is an abundant number.\n", number);
    } else {
        printf("%d is not an abundant number.\n", number);
    }
    return 0;
}