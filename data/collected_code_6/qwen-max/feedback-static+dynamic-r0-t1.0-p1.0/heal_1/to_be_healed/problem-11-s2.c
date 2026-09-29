#include <stdio.h>
#include <string.h>

void remove_char_occurrences(char *str, char c) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int first = -1, last = -1, length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (str[i] == c) {
            if (first == -1) first = i;
            last = i;
        }
    }
    if (first != -1) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(&str[first], &str[first + 1], strlen(str + first) - 1);
        if (last != first) { 
            last--; 
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(&str[last], &str[last + 1], strlen(str + last));
    }
}

int main() {
    char str[] = "programming";
    char c = 'm';
    remove_char_occurrences(str, c);
    printf("%s\n", str);
    return 0;
}