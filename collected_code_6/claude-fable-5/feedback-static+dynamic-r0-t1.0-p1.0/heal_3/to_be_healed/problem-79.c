#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 256

bool is_word_length_odd(const char *word, size_t max_length)
{
    size_t length;

    if (word == NULL) {
        return false;
    }

    length = strnlen(word, max_length);
    return (length % 2U) != 0U;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_WORD_LENGTH];
    size_t length;

    printf("Enter a word: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    length = strnlen(buffer, sizeof(buffer));
    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
    } else if (length == sizeof(buffer) - 1U) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    if (buffer[0] == '\0') {
        fprintf(stderr, "Error: empty input.\n");
        return 1;
    }

    if (is_word_length_odd(buffer, sizeof(buffer))) {
        printf("The length of the word \"%s\" is odd.\n", buffer);
    } else {
        printf("The length of the word \"%s\" is even.\n", buffer);
    }

    return 0;
}