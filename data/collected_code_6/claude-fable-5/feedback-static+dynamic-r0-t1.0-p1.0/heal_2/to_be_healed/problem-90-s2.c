#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

size_t longest_word_length(const char *str, size_t max_size)
{
    size_t max_len = 0;
    size_t current_len = 0;
    size_t i = 0;

    if (str == NULL) {
        return 0;
    }

    while (i < max_size && str[i] != '\0') {
        if (isspace((unsigned char)str[i])) {
            if (current_len > max_len) {
                max_len = current_len;
            }
            current_len = 0;
        } else {
            current_len++;
        }
        i++;
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
    char buffer[BUFFER_SIZE];
    size_t result;
    size_t len;

    if (printf("Enter a sentence: ") < 0) {
        return EXIT_FAILURE;
    }

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = longest_word_length(buffer, sizeof(buffer));

    if (printf("Length of the longest word: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}