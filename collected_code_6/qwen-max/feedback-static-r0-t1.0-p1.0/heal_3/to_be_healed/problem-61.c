#include <stdio.h>
#include <string.h>

int count_matching_substrings(const char *str, size_t length) {
    int counter = 0;
    for (size_t i = 0; i < length; i++) {
        int sum = 0;
        for (size_t len = 1; i + len <= length; len++) {
            if (i + len - 1 < length) {
                sum += str[i + len - 1] - '0';
                if (sum == len) {
                    counter++;
                }
            }
        }
    }
    return counter;
}

int main() {
    const char *input = "1112223";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_length = strlen(input);
    int result = count_matching_substrings(input, input_length);
    printf("Number of substrings: %d\n", result);
    return 0;
}