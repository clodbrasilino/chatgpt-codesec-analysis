#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 2 failed: expected False, got <no output>
  */

int is_perfect_square(int num) {
    if (num < 0) {
        return 0;
    }
    if (num == 0) {
        return 1;
    }
    long low = 1;
    long high = num;
    while (low <= high) {
        long mid = low + (high - low) / 2;
        long square = mid * mid;
        if (square == num) {
            return 1;
        } else if (square < num) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 2147483647) {
        fprintf(stderr, "Invalid input: must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    int num = (int)val;
    printf("%s\n", is_perfect_square(num) ? "True" : "False");
    return EXIT_SUCCESS;
}