#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int contains_all_vowels(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int a_found = 0, e_found = 0, i_found = 0, o_found = 0, u_found = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    for (size_t idx = 0; idx < len; idx++) {
        char ch = tolower((unsigned char)str[idx]);
        if (ch == 'a') {
            a_found = 1;
        } else if (ch == 'e') {
            e_found = 1;
        } else if (ch == 'i') {
            i_found = 1;
        } else if (ch == 'o') {
            o_found = 1;
        } else if (ch == 'u') {
            u_found = 1;
        }

        if (a_found && e_found && i_found && o_found && u_found) {
            return 1;
        }
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

    if (contains_all_vowels(argv[1])) {
        printf("Accepted\n");
    } else {
        printf("Rejected\n");
    }

    return EXIT_SUCCESS;
}