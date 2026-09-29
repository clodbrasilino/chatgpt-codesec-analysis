#include <stdio.h>
#include <stdlib.h>

int check_divisor_count_parity(long long n) {
    if (n <= 0) {
        return -1;
    }
    long long i = 1;
    long long count = 0;
    while (i * i <= n) {
        if (n % i == 0) {
            if (i * i == n) {
                count++;
            } else {
                count += 2;
            }
        }
        i++;
    }
    return count % 2;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    long long num;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%lld", &num) != 1) {
        return EXIT_FAILURE;
    }
    int result = check_divisor_count_parity(num);
    if (result == -1) {
        return EXIT_FAILURE;
    }
    printf("%d\n", result);
    return EXIT_SUCCESS;
}