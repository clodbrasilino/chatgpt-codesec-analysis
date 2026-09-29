#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int64_t nth_hexagonal_number(int64_t n) {
    int64_t max_n = 9223372036854775807 / 2;
    if (n > max_n) {
        return -1;
    }
    int64_t result = n * (2 * n - 1);
    return result;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) == 1 && n > 0) {
        int64_t hex_num = nth_hexagonal_number(n);
        if (hex_num == -1) {
            printf("Integer overflow occurred. Please enter a smaller positive integer.\n");
        } else {
            printf("The %ldth hexagonal number is: %ld\n", n, hex_num);
        }
    } else {
        printf("Invalid input. Please enter a positive integer.\n");
    }
    return 0;
}