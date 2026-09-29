#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 24, got <no output>
  *  test case 2 failed: expected 32, got <no output>
  *  test case 0 failed: expected 21, got <no output>
  */

int octalToDecimal(long octal) {
    long decimal = 0, i = 0;
    while (octal != 0) {
        decimal += (octal % 10) * (long)pow(8, i);
        ++i;
        octal /= 10;
    }
    return (int)decimal;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[16];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        char *end;
        long num = strtol(input, &end, 8);

        if (num >= INT_MIN && num <= INT_MAX && *input != '\n' && (*end == '\n' || (*end == ' ' && end[1] == '\n')) && end > input) {
            printf("%d\n", octalToDecimal(num));
        } else {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stderr, "Input error\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}