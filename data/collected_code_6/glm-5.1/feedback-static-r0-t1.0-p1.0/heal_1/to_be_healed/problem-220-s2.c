#include <stdio.h>
#include <string.h>

void replace_chars(char *str, int n) {
    if (str == NULL || n <= 0) {
        return;
    }
    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
            count++;
            if (count == n) {
                break;
            }
        }
    }
}

int main(void) {
    char text[] = "hello, world. this is a test, with spaces.";
    printf("Original: %s\n", text);
    replace_chars(text, 3);
    printf("Modified: %s\n", text);
    return 0;
}