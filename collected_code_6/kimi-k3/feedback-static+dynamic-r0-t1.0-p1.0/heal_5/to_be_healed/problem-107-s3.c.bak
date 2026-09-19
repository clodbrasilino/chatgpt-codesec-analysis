#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 0, got 2
  *  test case 0 failed: expected 6, got 5
  */

int count_hexadecimal_numbers(unsigned long long start, unsigned long long end) {
    if (start > end) {
        return -1;
    }
    
    if (end - start > 2147483647ULL) {
        return -1;
    }
    
    return (int)(end - start);
}

int main(void) {
    unsigned long long start, end;
    int result;

    if (scanf("%llu", &start) != 1) {
        return EXIT_FAILURE;
    }

    if (scanf("%llu", &end) != 1) {
        return EXIT_FAILURE;
    }

    result = count_hexadecimal_numbers(start, end);

    if (result < 0) {
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}