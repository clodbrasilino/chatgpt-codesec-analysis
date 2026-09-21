#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int starts_ends_same(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    return str[0] == str[len - 1];
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }

    if (starts_ends_same(argv[1])) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}