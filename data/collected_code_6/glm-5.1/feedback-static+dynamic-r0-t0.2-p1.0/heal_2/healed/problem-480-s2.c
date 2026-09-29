#include <stdio.h>
#include <string.h>
#include <stdint.h>

char find_max_occurring_char(const char *str, size_t max_len) {
    int count[256] = {0};
    int max_count = 0;
    char max_char = '\0';

    if (str == NULL) {
        return '\0';
    }

    size_t len = strnlen(str, max_len);
    for (size_t i = 0; i < len; i++) {
        unsigned char c = str[i];
        count[c]++;
        if (count[c] > max_count) {
            max_count = count[c];
            max_char = str[i];
        }
    }

    return max_char;
}

int main(int argc, char *argv[]) {
    const char *test_str = "experience";
    char result = find_max_occurring_char(test_str, SIZE_MAX);

    if (result != '\0') {
        printf("%c\n", result);
    }

    return 0;
}