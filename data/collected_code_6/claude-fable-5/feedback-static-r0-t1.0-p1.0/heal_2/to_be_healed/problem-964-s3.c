#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 256U

bool is_word_length_even(const char *word, size_t max_len)
{
    size_t len;

    if (word == NULL) {
        return false;
    }

    len = strnlen(word, max_len);
    if (len == max_len) {
        return false;
    }

    return (len % 2U) == 0U;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    size_t len;

    printf("Enter a word: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
        len--;
    }

    if (len == 0U) {
        fprintf(stderr, "No word entered\n");
        return EXIT_FAILURE;
    }

    if (len == sizeof(buffer) - 1U && buffer[len - 1U] != '\0') {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    if (is_word_length_even(buffer, sizeof(buffer))) {
        printf("The word \"%s\" has an even length (%zu)\n", buffer, len);
    } else {
        printf("The word \"%s\" has an odd length (%zu)\n", buffer, len);
    }

    return EXIT_SUCCESS;
}