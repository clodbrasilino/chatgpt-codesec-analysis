#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int remove_digits_from_strings(char **strings, size_t count) {
    if (strings == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        char *write = strings[i];
        char *read = strings[i];

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (*read != '\0') {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            if (!isdigit((unsigned char)*read)) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                *write = *read;
                write++;
            }
            read++;
        }
        *write = '\0';
    }

    return 0;
}

int main(void) {
    const char *original[] = {
        "Hello123 World456",
        "C0d1ng2 is3 f4n5",
        "NoDigitsHere",
        "12345",
        ""
    };

    size_t count = sizeof(original) / sizeof(original[0]);
    char **strings = malloc(count * sizeof(char *));
    if (strings == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(original[i]);
        strings[i] = malloc(len + 1);
        if (strings[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return EXIT_FAILURE;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(strings[i], original[i]);
    }

    if (remove_digits_from_strings(strings, count) != 0) {
        for (size_t i = 0; i < count; i++) {
            free(strings[i]);
        }
        free(strings);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }

    for (size_t i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);

    return EXIT_SUCCESS;
}