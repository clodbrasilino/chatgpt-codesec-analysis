#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>

void capitalize_first_last(char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t i = 0;

    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            i++;
        }
        if (i >= len) break;

        size_t start = i;
        while (i < len && !isspace((unsigned char)str[i])) {
            i++;
        }
        size_t end = i - 1;

        str[start] = (char)toupper((unsigned char)str[start]);
        str[end] = (char)toupper((unsigned char)str[end]);
    }
}

int main(void) {
    char text[] = "hello world from c programming";

    capitalize_first_last(text);
    printf("%s\n", text);

    return 0;
}