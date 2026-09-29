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
                size_t j;
                if (len >= result_size) {
                    return -1;
                }
                for (j = 0; j < len; j++) {
                    result[j] = text[start + j];
                }
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
    size_t i;

    for (i = 0; i < sizeof(sentences) / sizeof(sentences[0]); i++) {
        size_t buf_size;
        char *word;
        int status;

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        buf_size = strlen(sentences[i]) + 1;
        word = (char *)malloc(buf_size);
        if (word == NULL) {
            fprintf(stderr, "Memory allocation failure\n");
            return EXIT_FAILURE;
        }

        status = match_word_with_z(sentences[i], word, buf_size);
        if (status < 0) {
            fprintf(stderr, "Error processing input: %s\n", sentences[i]);
            free(word);
            return EXIT_FAILURE;
        }
        if (status == 1) {
            if (printf("Input: \"%s\" -> matched word: \"%s\"\n", sentences[i], word) < 0) {
                free(word);
                return EXIT_FAILURE;
            }
        } else {
            if (printf("Input: \"%s\" -> no word containing 'z' found\n", sentences[i]) < 0) {
                free(word);
                return EXIT_FAILURE;
            }
        }

        free(word);
    }

    return EXIT_SUCCESS;
}