#include <stdio.h>
#include <string.h>
#include <ctype.h>

int first_max_even_word_length(const char *str) {
    int max_len = 0;
    int current_len = 0;
    int in_word = 0;
    const char *p = str;

    while (*p != '\0') {
        if (isalpha((unsigned char)*p)) {
            if (!in_word) {
                in_word = 1;
                current_len = 1;
            } else {
                current_len++;
            }
        } else {
            if (in_word) {
                if (current_len % 2 == 0 && current_len > max_len) {
                    max_len = current_len;
                }
                in_word = 0;
                current_len = 0;
            }
        }
        p++;
    }

    if (in_word) {
        if (current_len % 2 == 0 && current_len > max_len) {
            max_len = current_len;
        }
    }

    return max_len;
}

int main(void) {
    char input[1024];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    int result = first_max_even_word_length(input);
    printf("First maximum even word length: %d\n", result);

    return 0;
}