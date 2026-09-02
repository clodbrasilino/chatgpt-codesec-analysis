#include <stdio.h>
#include <string.h>

int find_first_max_even_length(const char *str) {
    int max_len = 0;
    const char *word_start = str;
    while (*str) {
        if (*str == ' ') {
            int len = str - word_start;
            if (len > max_len && len % 2 == 0) {
                max_len = len;
            }
            word_start = str + 1;
        }
        str++;
    }
    int len = str - word_start;
    if (len > max_len && len % 2 == 0) {
        max_len = len;
    }
    return max_len;
}

int main() {
    const char *input = "this is a test string with even length words";
    int result = find_first_max_even_length(input);
    printf("First maximum even length: %d\n", result);
    return 0;
}