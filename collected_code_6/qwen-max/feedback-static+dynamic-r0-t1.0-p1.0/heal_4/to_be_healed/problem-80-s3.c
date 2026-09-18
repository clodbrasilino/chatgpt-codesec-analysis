#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

long nth_tetrahedral_number(long n) {
    if (n <= 0) return 0;
    long max_div_6 = LONG_MAX / 6;
    if (n > (long)((sqrt(8 * (double)max_div_6 + 1) - 1) / 2)) {
        fprintf(stderr, "Input too large, would cause overflow.\n");
        exit(EXIT_FAILURE);
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3086419746913580 * 55555557 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:672,execs:270,op:havoc,rep:5)
     */
    return n * (n + 1) * (n + 2) / 6;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }
    long result = nth_tetrahedral_number(n);
    printf("The %ldth tetrahedral number is: %ld\n", n, result);
    return 0;
}