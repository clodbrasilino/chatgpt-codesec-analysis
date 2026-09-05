#include <stdio.h>
#include <stdlib.h>

int find_difference(int num) {
    int even_sum = 0;
    int odd_sum = 0;

    if (num == 0) {
        return 0;
    }

    long long safe_num = num;

    if (safe_num < 0) {
        safe_num = -safe_num;
    }

    while (safe_num > 0) {
        int digit = safe_num % 10;
        if (digit % 2 == 0) {
            even_sum += digit;
        } else {
            odd_sum += digit;
        }
        safe_num /= 10;
    }

    return even_sum - odd_sum;
}

int main(int argc, char *argv[]) {
    int number = 123456;
    int result = find_difference(number);
    printf("%d\n", result);
    return 0;
}