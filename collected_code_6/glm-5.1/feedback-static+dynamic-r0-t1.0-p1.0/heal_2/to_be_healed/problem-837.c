#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 153, got <no output>
  *  test case 0 failed: expected 28, got <no output>
  *  test case 2 failed: expected 496, got <no output>
  */

unsigned long long cube_sum_odd(int n) {
    if (n <= 0) {
        return 0;
    }

    unsigned long long sum = 0;
    int num = 1;

    while (n > 0) {
        sum += (unsigned long long)num * num * num;
        num += 2;
        n--;
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || val <= 0 || val > 10000) {
        fprintf(stderr, "Error: n must be a positive integer within safe limits.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = cube_sum_odd((int)val);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}