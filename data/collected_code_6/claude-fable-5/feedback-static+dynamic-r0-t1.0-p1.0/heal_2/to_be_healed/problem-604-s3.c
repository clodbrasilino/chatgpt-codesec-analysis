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

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_SIZE];
    char *newline;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    newline = strchr(input, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

    if (reverse_words(input, sizeof(input)) != 0) {
        fprintf(stderr, "Error reversing words\n");
        return EXIT_FAILURE;
    }

    printf("Reversed: %s\n", input);

    return EXIT_SUCCESS;
}