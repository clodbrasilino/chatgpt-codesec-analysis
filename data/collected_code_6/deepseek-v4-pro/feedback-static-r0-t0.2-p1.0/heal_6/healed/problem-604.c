#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>

void reverse_range(char *start, char *end) {
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

char *reverse_words(char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (len < INT_MAX && str[len] != '\0') {
        len++;
    }
    if (len == INT_MAX) {
        return NULL;
    }
    if (len == 0) {
        return str;
    }

    reverse_range(str, str + len - 1);

    char *word_start = str;
    char *p = str;

    while (*p != '\0') {
        if (*p == ' ') {
            reverse_range(word_start, p - 1);
            word_start = p + 1;
        }
        p++;
    }

    reverse_range(word_start, p - 1);

    return str;
}

int main(void) {
    char *input = NULL;
    size_t buffer_size = 256;

    input = (char *)malloc(buffer_size);
    if (input == NULL) {
        return 1;
    }

    printf("Enter a string: ");
    if (fgets(input, (int)buffer_size, stdin) == NULL) {
        free(input);
        return 1;
    }

    size_t input_len = 0;
    while (input_len < buffer_size && input[input_len] != '\0') {
        input_len++;
    }

    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
    } else {
        if (input_len == buffer_size && input[buffer_size - 1] != '\0') {
            input[buffer_size - 1] = '\0';
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Input too long, truncation occurred.\n");
        if (input_len == buffer_size) {
            input[buffer_size - 1] = '\0';
        }
    }

    reverse_words(input);

    printf("Reversed words: %s\n", input);

    free(input);
    return 0;
}