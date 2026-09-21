#include <stdio.h>
#include <string.h>

int countSubstringsWithSameStartEnd(const char *str, size_t length) {
    int count = 0;
    for (size_t i = 0; i < length; ++i) {
        for (size_t j = i + 1; j < length; ++j) {
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
    size_t input_length = strlen(input);
    int result = countSubstringsWithSameStartEnd(input, input_length);
    printf("Number of substrings starting and ending with the same character: %d\n", result);
    return 0;
}