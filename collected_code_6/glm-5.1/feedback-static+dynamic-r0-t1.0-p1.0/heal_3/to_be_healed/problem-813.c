#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got <no output>
  *  test case 0 failed: expected 6, got <no output>
  *  test case 2 failed: expected 8, got <no output>
  */

size_t string_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    return len;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = string_length(argv[1]);
    printf("%zu\n", len);

    return EXIT_SUCCESS;
}