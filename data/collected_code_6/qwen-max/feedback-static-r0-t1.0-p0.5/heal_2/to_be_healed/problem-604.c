#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str) {
    char *word = strtok(str, " ");
    char **reversed = (char **)malloc(50 * sizeof(char *));
    int i = 0;

    while (word != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        reversed[i] = (char *)malloc(strlen(word) + 1);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(reversed[i], word, strlen(word) + 1);
        word = strtok(NULL, " ");
        i++;
    }

    for (int j = 0; j < i / 2; j++) {
        char *temp = reversed[j];
        reversed[j] = reversed[i - j - 1];
        reversed[i - j - 1] = temp;
    }

    str[0] = '\0'; // Clear the original string
    for (int j = 0; j < i; j++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(str, reversed[j], strlen(reversed[j]) + 1);
        if (j < i - 1) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strncat(str, " ", 2);
        }
        free(reversed[j]);
    }
    free(reversed);
}

int main() {
    char str[] = "Hello World This is C";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    char *newStr = (char *)malloc(len + 1);
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(newStr, str);
    reverseWords(newStr);
    printf("%s\n", newStr);
    free(newStr);
    return 0;
}