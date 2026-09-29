#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_INPUT_LENGTH = 4096 };

static int contains_z(const char *word)
{
    return word != NULL && strchr(word, 'z') != NULL;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_INPUT_LENGTH + 2];

    if (fgets(word, sizeof word, stdin) == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    size_t length = strcspn(word, "\r\n");

    if (word[length] == '\0' && length == MAX_INPUT_LENGTH + 1) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != EOF && ch != '\n' && ch != '\r') {
        }

        return EXIT_FAILURE;
    }

    word[length] = '\0';
    puts(contains_z(word) ? "match" : "no match");

    return EXIT_SUCCESS;
}