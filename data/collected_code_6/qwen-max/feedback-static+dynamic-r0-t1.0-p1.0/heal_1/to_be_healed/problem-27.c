#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_digits(char *str) {
    int i, j = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    for (i = 0; i < len; i++) {
        if (!isdigit((unsigned char)str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char *strings[] = {"123abc456", "789def012", "345ghi678"};
    int num_strings = sizeof(strings) / sizeof(strings[0]);

    for (int i = 0; i < num_strings; i++) {
        remove_digits(strings[i]);
        printf("%s\n", strings[i]);
    }

    return 0;
}