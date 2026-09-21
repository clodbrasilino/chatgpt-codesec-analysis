#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT 256
#define MAX_DISCARD 4096

static void reverse_range(char *str, size_t start, size_t end)
{
    while (start < end) {
        char tmp = str[start];
        str[start] = str[end];
        str[end] = tmp;
        start++;
        end--;
    }
}

int reverse_words(char *str, size_t max_len)
{
    size_t len;
    size_t i;

    if (str == NULL || max_len == 0) {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len == max_len) {
        return -1;
    }
    if (len == 0) {
        return 0;
    }

    reverse_range(str, 0, len - 1);

    i = 0;
    while (i < len) {
        while (i < len && str[i] == ' ') {
            i++;
        }
        if (i >= len) {
            break;
        }
        size_t word_start = i;
        while (i < len && str[i] != ' ') {
            i++;
        }
        reverse_range(str, word_start, i - 1);
    }

    return 0;
}

static void discard_remaining_input(void)
{
    size_t count = 0;

    while (count < MAX_DISCARD) {
        int ch = fgetc(stdin);
        if (ch == '\n' || ch == EOF) {
            break;
        }
        count++;
    }
}

int main(void)
{
    char *input;
    char *newline;

    input = calloc(MAX_INPUT, sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    input[MAX_INPUT - 1] = '\0';

    newline = strchr(input, '\n');
    if (newline != NULL) {
        *newline = '\0';
    } else {
        discard_remaining_input();
    }

    if (reverse_words(input, MAX_INPUT) != 0) {
        fprintf(stderr, "Error reversing words\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Reversed: %s\n", input);

    free(input);
    return EXIT_SUCCESS;
}