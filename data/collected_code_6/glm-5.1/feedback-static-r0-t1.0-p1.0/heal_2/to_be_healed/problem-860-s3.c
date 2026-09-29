#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ends_with_alphanumeric(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return 0;
    }

    char last = str[len - 1];
    if ((last >= 'a' && last <= 'z') || (last >= 'A' && last <= 'Z') || (last >= '0' && last <= '9')) {
        return 1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (ends_with_alphanumeric(argv[1], strlen(argv[1]))) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return EXIT_SUCCESS;
}