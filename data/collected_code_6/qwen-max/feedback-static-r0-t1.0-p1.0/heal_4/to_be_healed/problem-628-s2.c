#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void replace_spaces(char *str) {
    if (str == NULL) return;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    int count = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') count++;
    }

    size_t new_length = len + (count * 2);
    char *new_str = (char *)malloc(new_length + 1);
    if (new_str == NULL) return;

    for (ssize_t i = len - 1, j = new_length - 1; i >= 0; i--, j--) {
        if (str[i] == ' ') {
            new_str[j] = '0';
            new_str[j - 1] = '2';
            new_str[j - 2] = '%';
            j -= 2;
        } else {
            new_str[j] = str[i];
        }
    }
    new_str[new_length] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str, new_str, new_length + 1);
    free(new_str);
}

int main() {
    char str1[] = "Mr John Smith    ";
    replace_spaces(str1);
    printf("Replaced string: %s\n", str1);

    char str2[] = " Test String with Spaces  ";
    replace_spaces(str2);
    printf("Replaced string: %s\n", str2);

    return 0;
}