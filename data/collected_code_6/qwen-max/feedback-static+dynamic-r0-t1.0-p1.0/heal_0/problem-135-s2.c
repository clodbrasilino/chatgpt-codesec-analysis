#include <stdio.h>

long nth_hexagonal_number(long n) {
    return n * (2 * n - 1);
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) == 1 && n > 0) {
        long hex_num = nth_hexagonal_number(n);
        printf("The %ldth hexagonal number is: %ld\n", n, hex_num);
    } else {
        printf("Invalid input. Please enter a positive integer.\n");
    }
    return 0;
}