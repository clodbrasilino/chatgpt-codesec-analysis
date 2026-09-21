#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str, size_t len) {
    char *copy = malloc(len + 1);
    if (copy == NULL) return;
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(copy, str, len + 1);

    char *word = strtok(copy, " ");
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *reversed[50];
    int i = 0;

    while (word != NULL && i < 50) {
        reversed[i++] = strdup(word);
        word = strtok(NULL, " ");
    }

    str[0] = '\0';
    for (int j = i - 1; j >= 0; j--) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t space = strlen(str);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t word_len = strlen(reversed[j]);
        if (space + word_len + 1 <= len) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(str, reversed[j]);
            if (j > 0 && space + word_len + 2 <= len) {
                /* Possible weaknesses found:
                 * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
                 */
                strcat(str, " ");
            }
        }
        free(reversed[j]);
    }

    free(copy);
}

int main() {
    char str[] = "Hello World This is C";
    reverseWords(str, sizeof(str) - 1);
    printf("%s\n", str);
    return 0;
}