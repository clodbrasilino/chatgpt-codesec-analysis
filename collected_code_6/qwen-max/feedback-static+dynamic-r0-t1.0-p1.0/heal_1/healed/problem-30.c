#include <stdio.h>
#include <string.h>

int countSubstringsWithSameStartEnd(const char *str, size_t len) {
    int count = 0;
    for (size_t i = 0; i < len; ++i) {
        for (size_t j = i + 1; j < len; ++j) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    const char *input = "abcab";
    size_t input_len = strlen(input);
    int result = countSubstringsWithSameStartEnd(input, input_len);
    printf("Number of substrings starting and ending with the same character: %d\n", result);
    return 0;
}