#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_digits(char *str, size_t len) {
    char *write = str;
    for (char *read = str; read - str < len && write - str < len; read++) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (!isdigit((unsigned char)*read)) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            *write++ = *read;
        }
    }
    *write = '\0';
}

int main() {
    char strings[][20] = {"hello123", "world4567", "test890"};
    int num_strings = sizeof(strings) / sizeof(strings[0]);

    for (int i = 0; i < num_strings; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        remove_digits(strings[i], strlen(strings[i]));
        printf("%s\n", strings[i]);
    }

    return 0;
}