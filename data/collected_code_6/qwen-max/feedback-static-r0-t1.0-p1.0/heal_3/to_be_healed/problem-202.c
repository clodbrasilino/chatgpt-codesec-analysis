#include <stdio.h>
#include <string.h>

void remove_even_chars(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int i, j, len = strlen(str);
    for (i = 0; i < len; ) {
        if ((i % 2) == 0 && i != 0) {
            for (j = i; j < len - 1; j++) {
                str[j] = str[j + 1];
            }
            len--;
            str[len] = '\0';
        } else {
            i++;
        }
    }
}

int main() {
    char str[] = "abcdefghijklmnopqrstuvwxyz";
    printf("Original String: %s\n", str);
    remove_even_chars(str);
    printf("Modified String: %s\n", str);
    return 0;
}