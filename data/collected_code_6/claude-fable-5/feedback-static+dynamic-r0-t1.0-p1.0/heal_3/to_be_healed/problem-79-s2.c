#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORD_LEN 256

static bool is_length_odd(const char *word, size_t max_len)
{
    size_t len;

    if (word == NULL) {
        return false;
    }

    len = strnlen(word, max_len);
    return (len % 2U) != 0U;
}

static void discard_remaining_input(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_WORD_LEN] = {0};
    size_t len;

    printf("Enter a word: ");
    fflush(stdout);

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));

    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
    } else if (len == sizeof(buffer) - 1U) {
        discard_remaining_input();
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