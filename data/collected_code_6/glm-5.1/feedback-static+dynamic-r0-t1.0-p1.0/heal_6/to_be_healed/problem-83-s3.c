#include <stdio.h>
#include <stdlib.h>

char find_char(const char *str) {
    unsigned int sum = 0;
    if (str == NULL) {
        return 0;
    }
    while (*str) {
        sum += (unsigned char)*str;
        str++;
    }
    return (char)(sum % 256);
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (argv[1][0] != '\0') {
        char result = find_char(argv[1]);
        printf("%c\n", result);
    }
    return EXIT_SUCCESS;
}