#include <stdio.h>
#include <string.h>

size_t replace_chars(char *str, size_t n, size_t len) {
    if (str == NULL || n == 0 || len == 0) {
        return 0;
    }

    size_t replaced = 0;
    for (size_t i = 0; i < len && i < strlen(str); ++i) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            if (replaced < n) {
                str[i] = ':';
                replaced++;
            }
        }
    }
    return replaced;
}

int main() {
    char input[] = "This is a test: replace, spaces, and. dots.";
    size_t n = 4;
    size_t count = replace_chars(input, n, sizeof(input));

    printf("Replaced %zu occurrences: %s\n", count, input);
    return 0;
}