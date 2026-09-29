#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t count_substrings(const char *str, size_t max_len) {
    size_t len = strnlen(str, max_len);
    return len * (len + 1) / 2;
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(argv[1]);
    size_t max_len = 1024;
    size_t bounded_len = len < max_len ? len : max_len;

    size_t count = count_substrings(argv[1], bounded_len);
    printf("%zu\n", count);

    return EXIT_SUCCESS;
}