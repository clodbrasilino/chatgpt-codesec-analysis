#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_words(char *str) {
    if (str == NULL) return;
    char *start, *end, temp;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    for (start = end = str; start <= str + len; start++) {
        if (*start == ' ' || *start == '\0') {
            start--;
            while (end < start) {
                temp = *end;
                *end = *start;
                *start = temp;
                end++;
                start--;
            }
            end = start + 2;
        }
    }
}

int main() {
    char str[] = "Hello World This is C";
    reverse_words(str);
    printf("%s\n", str);
    return 0;
}