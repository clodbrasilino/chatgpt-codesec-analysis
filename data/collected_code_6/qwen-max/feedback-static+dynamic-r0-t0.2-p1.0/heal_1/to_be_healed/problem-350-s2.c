#include <stdio.h>
#include <string.h>

int min_length_by_removing_char(const char *str, char ch) {
    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        if (str[i] == ch) {
            count++;
        }
    }
    return len - count;
}

int main() {
    const char *input = "programming";
    char ch = 'm';
    int result = min_length_by_removing_char(input, ch);
    printf("Minimized length: %d\n", result);
    return 0;
}