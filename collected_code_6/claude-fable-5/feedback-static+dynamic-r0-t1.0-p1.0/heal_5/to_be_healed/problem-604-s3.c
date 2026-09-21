#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 256

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
        size_t word_start;

        while (i < len && str[i] == ' ') {
            i++;
        }
        if (i >= len) {
            break;
        }
        word_start = i;
        while (i < len && str[i] != ' ') {
            i++;
        }
        reverse_range(str, word_start, i - 1);
    }

    return 0;
}

static void discard_remaining_input(void)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch == '\n' || ch == EOF) {
            break;
        }
    }
}

int main(void)
{
    char *input;
    char *newline;

    input = calloc(MAX_INPUT_SIZE, sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");
    if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    input[MAX_INPUT_SIZE - 1] = '\0';

    newline = strchr(input, '\n');
    if (newline != NULL) {
        *newline = '\0';
    } else {
        discard_remaining_input();
    }

    if (reverse_words(input, MAX_INPUT_SIZE) != 0) {
        fprintf(stderr, "Error reversing words\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Reversed: %s\n", input);

    free(input);
    return EXIT_SUCCESS;
}