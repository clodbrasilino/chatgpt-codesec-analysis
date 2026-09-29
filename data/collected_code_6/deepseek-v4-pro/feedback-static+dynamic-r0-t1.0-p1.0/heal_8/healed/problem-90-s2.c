#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>

#define MAX_STRING 1024

int longest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int max_length = 0;
    int current_length = 0;
    int in_word = 0;
    size_t pos = 0;

    while (str[pos] != '\0' && pos < MAX_STRING) {
        if (isalpha((unsigned char)str[pos])) {
            if (!in_word) {
                in_word = 1;
                current_length = 1;
            } else {
                current_length++;
            }
            if (current_length > max_length) {
                max_length = current_length;
            }
        } else {
            if (in_word) {
                in_word = 0;
                current_length = 0;
            }
        }
        pos++;
    }

    return max_length;
}

int main(void) {
    char input[MAX_STRING];
    int c;
    size_t i = 0;

    printf("Enter a string: ");

    while (i < sizeof(input) - 1) {
        c = getchar();
        if (c == EOF) {
            if (ferror(stdin)) {
                printf("Error reading input.\n");
                return 1;
            }
            break;
        }
        if (c == '\n') {
            break;
        }
        input[i++] = (char)c;
    }
    input[i] = '\0';

    if (i == 0 && c == EOF && ferror(stdin)) {
        printf("Error reading input.\n");
        return 1;
    }

    if (c != '\n' && c != EOF) {
        int discard;
        size_t discard_count = 0;
        while ((discard = getchar()) != '\n' && discard != EOF) {
            discard_count++;
            if (discard_count > MAX_STRING) {
                break;
            }
            if (discard == EOF && ferror(stdin)) {
                printf("Error reading input.\n");
                return 1;
            }
        }
    }

    int result = longest_word_length(input);
    printf("Longest word length: %d\n", result);

    return 0;
}