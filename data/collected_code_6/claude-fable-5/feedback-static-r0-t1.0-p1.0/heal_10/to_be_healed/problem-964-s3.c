#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 256U
#define MAX_DISCARD_ITERATIONS 65536U

static bool is_word_length_even(const char *word, size_t max_len)
{
    size_t len;

    if (word == NULL || max_len == 0U) {
        return false;
    }

    len = strnlen(word, max_len);
    if (len == max_len) {
        return false;
    }

    return (len % 2U) == 0U;
}

static void discard_remaining_input(void)
{
    int ch;
    size_t iterations = 0U;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        iterations++;
    } while (ch != '\n' && ch != EOF && iterations < MAX_DISCARD_ITERATIONS);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE] = {0};
    size_t len;
    bool newline_found;

    printf("Enter a word: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    newline_found = (len > 0U && buffer[len - 1U] == '\n');

    if (newline_found) {
        buffer[len - 1U] = '\0';
        len--;
    } else if (len == sizeof(buffer) - 1U) {
        discard_remaining_input();
    }

    if (len == 0U) {
        fprintf(stderr, "No word entered\n");
        return EXIT_FAILURE;
    }

    if (is_word_length_even(buffer, sizeof(buffer))) {
        printf("The word \"%s\" has an even length (%zu)\n", buffer, len);
    } else {
        printf("The word \"%s\" has an odd length (%zu)\n", buffer, len);
    }

    return EXIT_SUCCESS;
}