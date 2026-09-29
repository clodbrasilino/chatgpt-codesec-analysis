#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str) {
    char *word = strtok(str, " ");
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *temp = (char *)malloc(strlen(word) + 1);
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(temp, word);
    while (word != NULL) {
        word = strtok(NULL, " ");
        if (word != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            strncat(str, " ", strlen(str) + 1 - strlen(str));
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            strncat(str, word, strlen(str) + 1 - strlen(str));
        }
    }
    free(temp);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    temp = (char *)malloc(strlen(str) + 1);
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(temp, str);
    int i, j;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    for (i = 0; i < strlen(str); i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        for (j = i + 1; j < strlen(str); j++) {
            if (str[j] == ' ') {
                int start = i, end = j - 1;
                while (start < end) {
                    char t = str[start];
                    str[start] = str[end];
                    str[end] = t;
                    start++;
                    end--;
                }
                i = j;
                break;
            }
        }
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int start = i, end = strlen(str) - 1;
    while (start < end) {
        char t = str[start];
        str[start] = str[end];
        str[end] = t;
        start++;
        end--;
    }
    free(temp);
}

int main() {
    char str[] = "Hello World This is C";
    reverseWords(str);
    printf("%s\n", str);
    return 0;
}