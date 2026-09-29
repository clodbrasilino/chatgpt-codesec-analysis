#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_STRING 1024

int longest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int max_length = 0;
    int current_length = 0;
    int in_word = 0;
    size_t chars_read = 0;

    while (chars_read < MAX_STRING && str[chars_read] != '\0') {
        if (isalpha((unsigned char)str[chars_read])) {
            if (!in_word) {
                in_word = 1;
                current_length = 1;
            } else {
                current_length++;
            }
        } else {
            if (in_word) {
                if (current_length > max_length) {
                    max_length = current_length;
                }
                in_word = 0;
                current_length = 0;
            }
        }
        chars_read++;
    }

    if (in_word && current_length > max_length) {
        max_length = current_length;
    }

    return max_length;
}

int main(void) {
    char input[MAX_STRING];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1 && input[len - 1] != '\0') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == '\0') {
                break;
            }
        }
    }

    input[sizeof(input) - 1] = '\0';

    int result = longest_word_length(input);
    printf("Longest word length: %d\n", result);

    return 0;
}