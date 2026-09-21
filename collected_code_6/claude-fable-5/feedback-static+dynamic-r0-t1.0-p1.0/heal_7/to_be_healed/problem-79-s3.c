#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_WORD_LEN 256

static bool is_word_length_odd(const char *word)
{
    size_t len;

    if (word == NULL) {
        return false;
    }

    len = strnlen(word, MAX_WORD_LEN);
    return (len % 2U) != 0U;
}

static void discard_remaining_input(void)
{
    int ch;
    uint32_t guard = 0U;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        guard++;
    } while (ch != '\n' && ch != EOF && guard < UINT32_MAX);
}

static bool read_word(char *buffer, size_t buffer_size)
{
    size_t len;

    if (buffer == NULL || buffer_size < 2U) {
        return false;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return false;
    }

    buffer[buffer_size - 1U] = '\0';

    len = strnlen(buffer, buffer_size);
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
    } else if (len == buffer_size - 1U) {
        discard_remaining_input();
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_WORD_LEN] = {0};
    size_t len;

    printf("Enter a word: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (!read_word(buffer, sizeof(buffer))) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len == 0U) {
        fprintf(stderr, "No word entered\n");
        return EXIT_FAILURE;
    }

    if (is_word_length_odd(buffer)) {
        printf("The word length is odd\n");
    } else {
        printf("The word length is even\n");
    }

    return EXIT_SUCCESS;
}