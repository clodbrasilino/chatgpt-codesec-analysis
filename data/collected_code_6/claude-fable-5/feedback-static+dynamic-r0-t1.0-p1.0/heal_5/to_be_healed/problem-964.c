#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_WORD_LEN 128
#define FLUSH_GUARD_LIMIT 1048576U

bool is_word_length_even(const char *word, size_t max_len)
{
    size_t len;

    if (word == NULL || max_len == 0U) {
        return false;
    }

    len = strnlen(word, max_len);
    return (len % 2U) == 0U;
}

static void flush_stdin(void)
{
    int c;
    size_t guard = 0U;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
        guard++;
    } while (c != '\n' && c != EOF && guard < FLUSH_GUARD_LIMIT);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_WORD_LEN] = { 0 };
    size_t len;

    printf("Enter a word: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));

    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
        len--;
    } else if (len == sizeof(buffer) - 1U) {
        flush_stdin();
        fprintf(stderr, "Error: input too long (maximum %u characters).\n",
                (unsigned int)(MAX_WORD_LEN - 1U));
        return EXIT_FAILURE;
    }

    if (len == 0U) {
        fprintf(stderr, "Error: no word entered.\n");
        return EXIT_FAILURE;
    }

    if (is_word_length_even(buffer, sizeof(buffer))) {
        printf("The word \"%s\" has an even length (%zu).\n", buffer, len);
    } else {
        printf("The word \"%s\" has an odd length (%zu).\n", buffer, len);
    }

    return EXIT_SUCCESS;
}