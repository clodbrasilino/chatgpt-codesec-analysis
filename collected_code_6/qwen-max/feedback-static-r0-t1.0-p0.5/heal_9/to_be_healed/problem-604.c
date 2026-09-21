#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str) {
    char *saveptr;
    char *word = strtok_r(str, " ", &saveptr);
    char **reversed = (char **)malloc(50 * sizeof(char *));
    int i = 0;

    while (word != NULL && i < 50) {
        reversed[i] = strdup(word);
        word = strtok_r(NULL, " ", &saveptr);
        i++;
    }

    for (int j = 0; j < i / 2; j++) {
        char *temp = reversed[j];
        reversed[j] = reversed[i - j - 1];
        reversed[i - j - 1] = temp;
    }

    str[0] = '\0';
    size_t current_len = 0;
    for (int j = 0; j < i; j++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t word_len = strlen(reversed[j]);
        if (current_len + word_len + 1 > 500) {
            break;
        }
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(str, reversed[j], 500 - current_len - 1);
        current_len += word_len;
        if (j < i - 1) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strncat(str, " ", 500 - current_len - 1);
            current_len++;
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
    char *newStr = (char *)malloc(strlen(str) + 1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    snprintf(newStr, strlen(str) + 1, "%s", str);
    reverseWords(newStr);
    printf("%s\n", newStr);
    free(newStr);
    return 0;
}