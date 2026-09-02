#include <stdio.h>

long nth_hexagonal_number(long n) {
    return 2 * n * (2 * n - 1);
}

int main() {
    long n = 5;
    long result = nth_hexagonal_number(n);
    printf("The %ldth hexagonal number is: %ld\n", n, result);
    return 0;
}