#include <stdio.h>
#include <string.h>

int min_length_by_removing_char(const char *str, char ch) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == ch) {
            count++;
        }
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    return strlen(str) - count;
}

int main() {
    const char *input = "programming";
    char to_remove = 'm';
    int new_length = min_length_by_removing_char(input, to_remove);
    printf("New length: %d\n", new_length);
    return 0;
}