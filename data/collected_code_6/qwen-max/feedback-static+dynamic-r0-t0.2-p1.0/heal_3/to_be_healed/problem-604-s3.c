#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str) {
    char *word_start = str;
    char *temp = str;
    int len = 0;
    while (*temp) {
        temp++;
        len++;
    }
    char *result = (char *)malloc(len + 1);
    if (result == NULL) return;
    result[len] = '\0';
    temp = str;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str) - 1;

    while (*temp) {
        temp++;
        if (*temp == ' ' || *temp == '\0') {
            while (temp > word_start) {
                result[len--] = *--temp;
            }
            while (*temp == ' ') {
                result[len--] = *temp++;
            }
            word_start = temp;
        }
    }
    memmove(str, result, len + 2);
    free(result);
}

int main() {
    char str[] = "Hello World This is C";
    reverseWords(str);
    printf("%s\n", str);
    return 0;
}