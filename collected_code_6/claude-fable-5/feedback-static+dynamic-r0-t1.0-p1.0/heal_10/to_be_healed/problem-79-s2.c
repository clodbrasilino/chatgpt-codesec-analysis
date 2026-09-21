#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_WORD_LEN 256U

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t i = 0U;

    if (str == NULL) {
        return 0U;
    }

    while (i < max_len && str[i] != '\0') {
        i++;
    }

    return i;
}

static bool is_length_odd(const char *word, size_t max_len)
{
    size_t len;

    if (word == NULL) {
        return false;
    }

    len = bounded_strlen(word, max_len);
    return (len % 2U) != 0U;
}

static void discard_remaining_input(void)
{
    int ch;
    size_t guard = 0U;
    const size_t guard_limit = (size_t)INT_MAX;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        guard++;
    } while (ch != '\n' && ch != EOF && guard < guard_limit);
}

static bool read_word(char *buffer, size_t buffer_size)
{
    size_t len;

    if (buffer == NULL || buffer_size < 2U) {
        return false;
    }

    memset(buffer, 0, buffer_size);

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return false;
    }

    buffer[buffer_size - 1U] = '\0';

    len = bounded_strlen(buffer, buffer_size);

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
    char buffer[MAX_WORD_LEN];

    printf("Enter a word: ");

    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error flushing output\n");
        return EXIT_FAILURE;
    }

    if (!read_word(buffer, sizeof(buffer))) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (buffer[0] == '\0') {
        fprintf(stderr, "No word entered\n");
        return EXIT_FAILURE;
    }

    if (is_length_odd(buffer, sizeof(buffer))) {
        printf("The word \"%s\" has an odd length.\n", buffer);
    } else {
        printf("The word \"%s\" has an even length.\n", buffer);
    }

    return EXIT_SUCCESS;
}