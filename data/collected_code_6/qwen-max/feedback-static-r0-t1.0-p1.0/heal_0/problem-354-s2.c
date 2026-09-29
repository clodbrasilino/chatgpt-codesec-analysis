#include <stdio.h>

long find_tnth_arithmetic(long a, long d, long n) {
    return a + (n - 1) * d;
}

int main() {
    long a = 1;  // First term
    long d = 2;  // Common difference
    long n = 5;  // Nth term to find

    long result = find_tnth_arithmetic(a, d, n);
    printf("The %ld-th term of the arithmetic progression is: %ld\n", n, result);

    return 0;
}