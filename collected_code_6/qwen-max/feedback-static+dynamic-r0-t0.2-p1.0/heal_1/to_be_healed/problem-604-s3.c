#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str) {
    char *word_start = str;
    char *temp = str;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) return;
    result[len] = '\0';
    while (*temp) {
        temp++;
        if (*temp == ' ' || *temp == '\0') {
            while (temp > word_start) {
                len--;
                result[len] = *--temp;
            }
            while (*temp == ' ') {
                result[len--] = *temp++;
            }
            word_start = temp;
        }
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, result);
    free(result);
}

int main() {
    char str[] = "Hello World This is C";
    reverseWords(str);
    printf("%s\n", str);
    return 0;
}