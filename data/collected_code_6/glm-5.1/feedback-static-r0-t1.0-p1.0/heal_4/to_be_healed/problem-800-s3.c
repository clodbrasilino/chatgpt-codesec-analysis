#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

size_t remove_whitespace(char *str) {
    if (str == NULL) {
        return 0;
    }

    char *dst = str;
    char *src = str;
    size_t count = 0;

    while (*src != '\0') {
        if (!isspace((unsigned char)*src)) {
            *dst = *src;
            dst++;
            count++;
        }
        src++;
    }

    *dst = '\0';
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(argv[1]);
    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, argv[1], len + 1);

    remove_whitespace(buffer);

    printf("%s\n", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}