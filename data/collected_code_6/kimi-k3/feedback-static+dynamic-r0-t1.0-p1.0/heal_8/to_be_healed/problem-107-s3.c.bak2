#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 0, got 2
  *  test case 0 failed: expected 6, got 5
  */

int count_hexadecimal_numbers(unsigned long long start, unsigned long long end) {
    if (start > end) {
        return -1;
    }

    unsigned long long diff = end - start;

    if (diff >= (unsigned long long)INT32_MAX) {
        return -1;
    }

    return (int)(diff);
}

int main(void) {
    unsigned long long start, end;
    int result;

    if (scanf("%llx", &start) != 1) {
        fprintf(stderr, "Invalid input for start\n");
        return EXIT_FAILURE;
    }

    if (scanf("%llx", &end) != 1) {
        fprintf(stderr, "Invalid input for end\n");
        return EXIT_FAILURE;
    }

    result = count_hexadecimal_numbers(start, end);

    if (result < 0) {
        fprintf(stderr, "Invalid range or result too large\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}