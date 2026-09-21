#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>

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
    char *line = NULL;
    size_t line_cap = 0;
    ssize_t line_len;
    size_t result;

    line_len = getline(&line, &line_cap, stdin);
    if (line_len < 0) {
        fprintf(stderr, "Error reading input\n");
        free(line);
        return 1;
    }

    if (line_len > 0 && line[line_len - 1] == '\n') {
        line[line_len - 1] = '\0';
    }

    result = longest_word_length(line);

    free(line);

    if (printf("Longest word length: %zu\n", result) < 0) {
        return 1;
    }

    return 0;
}