#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

size_t longest_word_length(const char *str)
{
    size_t max_len = 0;
    size_t current_len = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            current_len++;
            if (current_len > max_len) {
                max_len = current_len;
            }
        } else {
            current_len = 0;
        }
    }

    return max_len;
}

int main(void)
{
    size_t buffer_size = 1024;
    char *buffer;
    size_t result;

    buffer = calloc(buffer_size, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[buffer_size - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    result = longest_word_length(buffer);

    if (printf("Longest word length: %zu\n", result) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}