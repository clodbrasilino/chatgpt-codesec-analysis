#include <stdio.h>
#include <string.h>

int countSubstringsWithSameFirstAndLastChar(const char *str, size_t str_len) {
    int count = 0;
    for (size_t i = 0; i < str_len; ++i) {
        for (size_t j = i; j < str_len; ++j) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    const char *input = "abcab";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    int result = countSubstringsWithSameFirstAndLastChar(input, input_len);
    printf("Number of substrings with the same first and last character: %d\n", result);
    return 0;
}