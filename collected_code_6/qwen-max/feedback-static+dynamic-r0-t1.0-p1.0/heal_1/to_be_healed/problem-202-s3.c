#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_even_characters(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    int idx = 0;
    for (int i = 0; i < len; i++) {
        if ((i + 1) % 2 != 0) {
            str[idx++] = str[i];
        }
    }
    str[idx] = '\0';
}

int main() {
    char input[] = "abcdef";
    remove_even_characters(input);
    printf("%s\n", input);
    return 0;
}