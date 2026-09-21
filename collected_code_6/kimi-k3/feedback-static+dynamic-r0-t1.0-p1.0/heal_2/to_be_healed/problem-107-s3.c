#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 0, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  *  test case 0 failed: expected 6, got <no output>
  */

int count_hexadecimal_numbers(unsigned long long start, unsigned long long end) {
    int count = 0;
    unsigned long long i;

    if (start > end) {
        return -1;
    }

    for (i = start; i <= end; i++) {
        if (i == 0) {
            count++;
        } else {
            unsigned long long temp = i;
            while (temp > 0) {
                temp >>= 4;
                count++;
            }
        }

        if (i == 0xFFFFFFFFFFFFFFFFULL) {
            break;
        }
    }

    return count;
}

int main(void) {
    unsigned long long start, end;
    int result;

    printf("Enter start of range (decimal): ");
    if (scanf("%llu", &start) != 1) {
        fprintf(stderr, "Invalid input for start\n");
        return EXIT_FAILURE;
    }

    printf("Enter end of range (decimal): ");
    if (scanf("%llu", &end) != 1) {
        fprintf(stderr, "Invalid input for end\n");
        return EXIT_FAILURE;
    }

    result = count_hexadecimal_numbers(start, end);

    if (result < 0) {
        fprintf(stderr, "Invalid range: start must be less than or equal to end\n");
        return EXIT_FAILURE;
    }

    printf("Count of hexadecimal numbers in range: %d\n", result);

    return EXIT_SUCCESS;
}