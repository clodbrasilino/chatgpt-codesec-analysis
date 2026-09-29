#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_char(const char *str, size_t len) {
    unsigned int sum = 0;
    if (str == NULL) {
        return 0;
    }
    for (size_t i = 0; i < len; i++) {
        sum += (unsigned char)str[i];
    }
    return (char)(sum % 256);
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
    char result = find_char(argv[1], len);
    printf("%c\n", result);
    return EXIT_SUCCESS;
}