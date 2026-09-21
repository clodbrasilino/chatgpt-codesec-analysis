#include <stdio.h>
#include <string.h>

void remove_char_occurrences(char *str, char c) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int length = strlen(str);
    int write_index = 0;

    for (int i = 0; i < length; i++) {
        if (str[i] != c) {
            str[write_index++] = str[i];
        }
    }
    str[write_index] = '\0';
}

int main() {
    char str[] = "programming";
    char c = 'm';
    remove_char_occurrences(str, c);
    printf("%s\n", str);
    return 0;
}