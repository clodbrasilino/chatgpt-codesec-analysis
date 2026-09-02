#include <stdio.h>

int count_digits(int num) {
    int count = 0;
    if (num < 0) {
        num = -num;
    }
    if (num == 0) {
        return 1;
    }
    while (num > 0) {
        count++;
        num /= 10;
    }
    return count;
}

int add_and_count_digits(int a, int b) {
    int sum = a + b;
    printf("Sum: %d\n", sum);
    printf("Number of digits: %d\n", count_digits(sum));
    return sum;
}

int main(void) {
    add_and_count_digits(12345, 6789);
    return 0;
}