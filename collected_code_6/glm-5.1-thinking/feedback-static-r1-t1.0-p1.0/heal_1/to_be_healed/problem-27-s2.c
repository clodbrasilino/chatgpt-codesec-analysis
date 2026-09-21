#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_digits_from_list(char **strings, size_t count) {
    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        char *src = strings[i];
        char *dest = strings[i];

        while (*src) {
            if (!isdigit((unsigned char)*src)) {
                *dest = *src;
                dest++;
            }
            src++;
        }
        *dest = '\0';

        size_t new_size = (dest - strings[i]) + 1;
        char *shrunk = realloc(strings[i], new_size);
        if (shrunk != NULL) {
            strings[i] = shrunk;
        }
    }
}

int main(void) {
    size_t count = 3;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *strings[3];

    for (size_t i = 0; i < count; i++) {
        strings[i] = malloc(50 * sizeof(char));
        if (strings[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(strings[j]);
            }
            return EXIT_FAILURE;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     */
    strcpy(strings[0], "Hell0 W0rld 123");
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     */
    strcpy(strings[1], "C Pr0gramm1ng 2023");
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     */
    strcpy(strings[2], "N0 D1g1ts H3r3!");

    remove_digits_from_list(strings, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
        free(strings[i]);
    }

    return EXIT_SUCCESS;
}