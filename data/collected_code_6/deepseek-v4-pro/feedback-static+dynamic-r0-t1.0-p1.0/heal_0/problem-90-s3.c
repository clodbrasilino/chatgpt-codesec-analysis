#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int longest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int max_length = 0;
    int current_length = 0;

    while (*str != '\0') {
        if (isalpha((unsigned char)*str)) {
            current_length++;
        } else {
            if (current_length > max_length) {
                max_length = current_length;
            }
            current_length = 0;
        }
        str++;
    }

    if (current_length > max_length) {
        max_length = current_length;
    }

    return max_length;
}

int main(void) {
    char buffer[1024];

    printf("Enter a sentence: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    int result = longest_word_length(buffer);
    printf("Longest word length: %d\n", result);

    return EXIT_SUCCESS;
}