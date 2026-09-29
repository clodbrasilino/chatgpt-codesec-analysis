#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got 1
  */

int is_non_prime(int n) {
    if (n <= 1) {
        return 0;
    }
    if (n == 2) {
        return 1;
    }
    if (n % 2 == 0) {
        return 1;
    }
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return 1;
        }
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }
    for (int i = 1; i < argc; i++) {
        char *endptr;
        long val = strtol(argv[i], &endptr, 10);
        if (*endptr != '\0' || val < 0 || val > 2147483647) {
            return EXIT_FAILURE;
        }
        int num = (int)val;
        if (is_non_prime(num)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }
    return EXIT_SUCCESS;
}