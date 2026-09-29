#include <stdio.h>
#include <stdlib.h>

int reverse_number(int num) {
    int rev = 0;
    int n = num;
    if (n < 0) {
        return -1;
    }
    while (n > 0) {
        if (rev > (2147483647 - n % 10) / 10) {
            return -1;
        }
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return rev;
}

int check_one_less_than_twice_reverse(int num) {
    if (num < 0) {
        return 0;
    }
    int rev = reverse_number(num);
    if (rev < 0) {
        return 0;
    }
    int twice_rev = rev * 2;
    if (twice_rev < 0) {
        return 0;
    }
    return num == twice_rev - 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    long val = strtol(argv[1], NULL, 10);
    if (val < 0 || val > 2147483647) {
        return EXIT_FAILURE;
    }
    int num = (int)val;
    int result = check_one_less_than_twice_reverse(num);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}