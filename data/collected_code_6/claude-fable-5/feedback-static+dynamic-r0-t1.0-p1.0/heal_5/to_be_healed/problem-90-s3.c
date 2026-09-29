#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    size_t result;

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    result = longest_word_length(buffer);

    if (printf("Longest word length: %zu\n", result) < 0) {
        return 1;
    }

    return 0;
}