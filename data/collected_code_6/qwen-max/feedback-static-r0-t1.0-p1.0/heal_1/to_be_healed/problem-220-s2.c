#include <stdio.h>
#include <string.h>

size_t replace_chars(char *str, size_t n) {
    if (str == NULL || n == 0) {
        return 0;
    }

    size_t replaced = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    for (size_t i = 0; i < strlen(str); ++i) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            if (replaced < n) {
                str[i] = ':';
                replaced++;
            }
        }
    }
    return replaced;
}

int main() {
    char input[] = "This is a test: replace, spaces, and. dots.";
    size_t n = 4;
    size_t count = replace_chars(input, n);

    printf("Replaced %zu occurrences: %s\n", count, input);
    return 0;
}