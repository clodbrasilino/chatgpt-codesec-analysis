#include <stdio.h>
#include <stdlib.h>

int sum_of_divisors(int n) {
    if (n <= 0) {
        return -1;
    }
    int sum = 0;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    return sum;
}

int are_divisor_sums_same(int a, int b) {
    if (a <= 0 || b <= 0) {
        return 0;
    }
    int sum_a = sum_of_divisors(a);
    int sum_b = sum_of_divisors(b);
    if (sum_a == -1 || sum_b == -1) {
        return 0;
    }
    return sum_a == sum_b;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long va = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }
    long vb = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }
    if (va <= 0 || va > 2147483647 || vb <= 0 || vb > 2147483647) {
        return EXIT_FAILURE;
    }
    int a = (int)va;
    int b = (int)vb;
    int result = are_divisor_sums_same(a, b);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}