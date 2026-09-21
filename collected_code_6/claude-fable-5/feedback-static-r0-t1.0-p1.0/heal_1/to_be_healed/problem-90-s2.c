#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

size_t longest_word_length(const char *str)
{
    size_t max_len = 0;
    size_t current_len = 0;
    size_t i = 0;

    if (str == NULL) {
        return 0;
    }

    while (str[i] != '\0') {
        if (isspace((unsigned char)str[i])) {
            if (current_len > max_len) {
                max_len = current_len;
            }
            current_len = 0;
        } else {
            current_len++;
        }
        i++;
    }

    if (current_len > max_len) {
        max_len = current_len;
    }

    return max_len;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    size_t result;
    size_t len;

    printf("Enter a sentence: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = longest_word_length(buffer);

    if (printf("Length of the longest word: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}