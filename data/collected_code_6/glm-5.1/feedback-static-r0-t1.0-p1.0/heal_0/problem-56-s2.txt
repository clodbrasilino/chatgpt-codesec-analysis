#include <stdio.h>
#include <stdlib.h>

int reverse_number(int n) {
    int rev = 0;
    int num = abs(n);
    while (num > 0) {
        if (rev > (INT_MAX - num % 10) / 10) {
            return -1;
        }
        rev = rev * 10 + num % 10;
        num /= 10;
    }
    return n < 0 ? -rev : rev;
}

int check_one_less_than_twice_reverse(int n) {
    int rev = reverse_number(n);
    if (rev < 0) {
        return 0;
    }
    if (rev > INT_MAX / 2) {
        return 0;
    }
    return n == 2 * rev - 1;
}

int main(void) {
    int val = 73;
    if (check_one_less_than_twice_reverse(val)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    return 0;
}