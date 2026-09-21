#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *str_to_lower(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    char *lower_str = malloc(len + 1);
    if (lower_str == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        lower_str[i] = tolower((unsigned char)str[i]);
    }
    lower_str[len] = '\0';

    return lower_str;
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

    char *result = str_to_lower(argv[1]);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(result);
    return EXIT_SUCCESS;
}