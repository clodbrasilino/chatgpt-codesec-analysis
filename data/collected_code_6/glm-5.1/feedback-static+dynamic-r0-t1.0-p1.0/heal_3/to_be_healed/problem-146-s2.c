#include <stdio.h>
#include <stdlib.h>

size_t find_total_ascii(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t total = 0;
    size_t i = 0;

    while (str[i] != '\0') {
        total += (unsigned char)str[i];
        i++;
    }

    return total;
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

    size_t result = find_total_ascii(argv[1]);
    printf("%zu\n", result);

    return EXIT_SUCCESS;
}