#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max_diff_substring(const char *binary_str, size_t length) {
    int max_diff = 0, current_diff = 0;
    for (size_t i = 0; i < length; ++i) {
        if (binary_str[i] == '0') {
            current_diff++;
        } else if (binary_str[i] == '1') {
            current_diff--;
        }
        if (current_diff < 0) {
            current_diff = 0;
        }
        if (current_diff > max_diff) {
            max_diff = current_diff;
        }
    }
    return max_diff;
}

int main() {
    char binary_string[] = "11000010001";
    size_t len = strlen(binary_string);
    int result = max_diff_substring(binary_string, len);
    printf("Maximum difference: %d\n", result);
    return 0;
}