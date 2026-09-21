#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int match_word_with_z(const char *text, char *result, size_t result_size);

int match_word_with_z(const char *text, char *result, size_t result_size)
{
    size_t i = 0;

    if (text == NULL || result == NULL || result_size == 0) {
        return -1;
    }

    result[0] = '\0';

    while (text[i] != '\0') {
        while (text[i] != '\0' && !isalpha((unsigned char)text[i])) {
            i++;
        }
        if (text[i] == '\0') {
            break;
        }

        {
            size_t start = i;
            int found = 0;

            while (text[i] != '\0' && isalpha((unsigned char)text[i])) {
                if (tolower((unsigned char)text[i]) == 'z') {
                    found = 1;
                }
                i++;
            }

            if (found) {
                size_t len = i - start;
                if (len >= result_size) {
                    return -1;
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
    const char *sentences[] = {
        "The lazy dog sleeps all day.",
        "A quick brown fox jumps.",
        "Zebras graze in the savanna."
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[256];
    size_t i;

    for (i = 0; i < sizeof(sentences) / sizeof(sentences[0]); i++) {
        int status = match_word_with_z(sentences[i], word, sizeof(word));
        if (status < 0) {
            fprintf(stderr, "Error processing input: %s\n", sentences[i]);
            return EXIT_FAILURE;
        }
        if (status == 1) {
            if (printf("Input: \"%s\" -> matched word: \"%s\"\n", sentences[i], word) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("Input: \"%s\" -> no word containing 'z' found\n", sentences[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}