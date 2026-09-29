#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t longest_word_length(const char *text)
{
    size_t longest = 0;
    size_t current = 0;

    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        unsigned char ch = (unsigned char)*text++;

        if (isalnum(ch)) {
            ++current;
            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0;
        }
    }

    return longest;
}

int main(void)
{
    size_t longest = 0;
    /* Possible weaknesses found:
     *  Variable 'current' is assigned a value that is never used. [unreadVariable]
     */
    size_t current = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    longest = longest_word_length(buffer);

    if (printf("%zu\n", longest) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}