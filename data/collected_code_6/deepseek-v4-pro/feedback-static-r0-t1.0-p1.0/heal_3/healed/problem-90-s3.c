#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int longest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int max_length = 0;
    int current_length = 0;
    size_t i = 0;

    while (str[i] != '\0') {
        if (isalpha((unsigned char)str[i])) {
            if (current_length < INT_MAX) {
                current_length++;
            } else {
                return max_length;
            }
        } else {
            if (current_length > max_length) {
                max_length = current_length;
            }
            current_length = 0;
        }
        i++;
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

    size_t len = strlen(buffer);

    if (len > 0 && buffer[len - 1] != '\n' && len == sizeof(buffer) - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == '\0') {
                break;
            }
        }
    }

    size_t pos = 0;
    while (pos < sizeof(buffer) && buffer[pos] != '\0' && buffer[pos] != '\n') {
        pos++;
    }
    if (pos < sizeof(buffer)) {
        buffer[pos] = '\0';
    }

    int result = longest_word_length(buffer);
    printf("Longest word length: %d\n", result);

    return EXIT_SUCCESS;
}