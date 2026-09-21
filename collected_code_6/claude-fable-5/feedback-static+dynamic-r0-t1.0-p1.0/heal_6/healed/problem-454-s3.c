#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_BUFFER_SIZE 256

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

                for (j = 0; j < len && j < result_size - 1; j++) {
                    result[j] = text[start + j];
                }
                result[j] = '\0';
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
    char *word;
    size_t i;

    word = (char *)calloc(WORD_BUFFER_SIZE, sizeof(char));
    if (word == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < sizeof(sentences) / sizeof(sentences[0]); i++) {
        int status;

        if (sentences[i] == NULL) {
            fprintf(stderr, "Invalid input at index %zu\n", i);
            free(word);
            return EXIT_FAILURE;
        }

        status = match_word_with_z(sentences[i], word, WORD_BUFFER_SIZE);
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

        memset(word, 0, WORD_BUFFER_SIZE);
    }

    free(word);
    return EXIT_SUCCESS;
}