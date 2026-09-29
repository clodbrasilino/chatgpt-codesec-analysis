#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

size_t longest_word_length(void)
{
    size_t max_len = 0;
    size_t current_len = 0;
    int c;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && c != '\n') {
        if (isspace((unsigned char)c)) {
            if (current_len > max_len) {
                max_len = current_len;
            }
            current_len = 0;
        } else {
            current_len++;
        }
    }

    if (current_len > max_len) {
        max_len = current_len;
    }

    return max_len;
}

int main(void)
{
    size_t result;

    result = longest_word_length();

    if (ferror(stdin)) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    if (printf("Longest word length: %zu\n", result) < 0) {
        return 1;
    }

    return 0;
}