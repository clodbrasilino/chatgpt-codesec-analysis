#include <stdio.h>
#include <string.h>

void reverse_word(char *start, char *end) {
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void reverse_words_in_string(char* str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int length = strlen(str);
    int start = 0;
    for (int i = 0; i <= length; i++) {
        if (str[i] == ' ' || str[i] == '\0') {
            if (i - start > 0) {
                reverse_word(&str[start], &str[i - 1]);
            }
            start = i + 1;
        }
    }
    if (start < length) {
        reverse_word(&str[start], &str[length - 1]);
    }
    reverse_word(str, &str[length - 1]);
}

int main() {
    char str[] = "Hello World This is C";
    reverse_words_in_string(str);
    printf("%s\n", str);
    return 0;
}