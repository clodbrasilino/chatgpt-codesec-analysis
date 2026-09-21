#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int match_word_with_z(const char *text, char *result, size_t result_size)
{
    size_t i = 0;

    if (text == NULL || result == NULL || result_size == 0) {
        return 0;
    }

    while (text[i] != '\0') {
        while (text[i] != '\0' && !isalpha((unsigned char)text[i])) {
            i++;
        }
        if (text[i] == '\0') {
            break;
        }
        {
            size_t start = i;
            int has_z = 0;

            while (text[i] != '\0' && isalpha((unsigned char)text[i])) {
                if (tolower((unsigned char)text[i]) == 'z') {
                    has_z = 1;
                }
                i++;
            }
            if (has_z) {
                size_t len = i - start;

                if (len >= result_size) {
                    return 0;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result, &text[start], len);
                result[len] = '\0';
                return 1;
            }
        }
    }
    return 0;
}

int main(void)
{
    const char *text = "The lazy dog jumped over the fence";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[256];

    if (match_word_with_z(text, result, sizeof(result))) {
        if (printf("Found word: %s\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No word containing 'z' found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}