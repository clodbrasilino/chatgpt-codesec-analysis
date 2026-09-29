#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

size_t shortest_word_length(const char *str)
{
    size_t min_len = 0;
    size_t current_len = 0;
    int found = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i])) {
            current_len++;
        } else {
            if (current_len > 0) {
                if (!found || current_len < min_len) {
                    min_len = current_len;
                    found = 1;
                }
                current_len = 0;
            }
        }
    }

    if (current_len > 0) {
        if (!found || current_len < min_len) {
            min_len = current_len;
        }
    }

    return min_len;
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
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = shortest_word_length(buffer);

    if (result == 0) {
        printf("No words found in input\n");
    } else {
        printf("Length of shortest word: %zu\n", result);
    }

    return EXIT_SUCCESS;
}