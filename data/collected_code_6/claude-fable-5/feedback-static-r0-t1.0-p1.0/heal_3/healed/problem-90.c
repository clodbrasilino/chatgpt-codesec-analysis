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
    char buffer[1024];
    size_t result;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = longest_word_length(buffer);

    if (printf("Longest word length: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}