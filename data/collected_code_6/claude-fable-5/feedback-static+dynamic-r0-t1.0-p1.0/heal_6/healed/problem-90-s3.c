#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>

size_t longest_word_length(const char *str)
{
    size_t max_len = 0;
    size_t current_len = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isspace((unsigned char)*str)) {
            if (current_len > max_len) {
                max_len = current_len;
            }
            current_len = 0;
        } else {
            current_len++;
        }
        str++;
    }

    if (current_len > max_len) {
        max_len = current_len;
    }

    return max_len;
}

int main(void)
{
    char buffer[1024];
    size_t result;
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = longest_word_length(buffer);

    if (printf("Longest word length: %zu\n", result) < 0) {
        return 1;
    }

    return 0;
}