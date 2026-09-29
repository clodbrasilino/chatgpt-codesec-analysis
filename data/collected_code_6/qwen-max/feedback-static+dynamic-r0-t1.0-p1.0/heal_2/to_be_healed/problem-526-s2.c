#include <stdio.h>
#include <string.h>
#include <ctype.h>

void capitalizeFirstLast(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    for (int i = 0, wordStart = 0; i <= len; i++) {
        if (i == 0 || (i < len && str[i-1] == ' ')) {
            wordStart = i;
            str[i] = toupper(str[i]);
        } else if (i < len && (str[i] == ' ' || (i == len - 1))) {
            if (wordStart < i - 1) {
                str[i-1] = toupper(str[i-1]);
            }
        }
    }
}

int main() {
    char str[] = "hello world this is a test";
    capitalizeFirstLast(str);
    printf("%s\n", str);
    return 0;
}