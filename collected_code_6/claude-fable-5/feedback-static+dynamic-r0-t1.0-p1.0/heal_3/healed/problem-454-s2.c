#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LEN 4096

int word_contains_z(const char *word)
{
    size_t i;

    if (word == NULL) {
        return 0;
    }

    for (i = 0; word[i] != '\0'; i++) {
        if (word[i] == 'z' || word[i] == 'Z') {
            return 1;
        }
    }

    return 0;
}

static size_t bounded_length(const char *text, size_t max_len)
{
    size_t i;

    for (i = 0; i < max_len; i++) {
        if (text[i] == '\0') {
            break;
        }
    }

    return i;
}

char *find_word_with_z(const char *text)
{
    size_t i;
    size_t len;

    if (text == NULL) {
        return NULL;
    }

    len = bounded_length(text, MAX_TEXT_LEN);
    i = 0;

    while (i < len) {
        size_t start;
        size_t end;

        while (i < len && !isalpha((unsigned char)text[i])) {
            i++;
        }

        start = i;

        while (i < len && isalpha((unsigned char)text[i])) {
            i++;
        }

        end = i;

        if (end > start) {
            size_t word_len = end - start;
            size_t j;
            int has_z = 0;

            for (j = start; j < end; j++) {
                if (text[j] == 'z' || text[j] == 'Z') {
                    has_z = 1;
                    break;
                }
            }

            if (has_z) {
                char *result;

                if (word_len >= MAX_TEXT_LEN) {
                    return NULL;
                }

                result = malloc(word_len + 1);
                if (result == NULL) {
                    return NULL;
                }

                memcpy(result, &text[start], word_len);
                result[word_len] = '\0';
                return result;
            }
        }
    }

    return NULL;
}

int main(void)
{
    const char *sentence = "The lazy dog jumped over the fuzzy fence";
    char *match;

    match = find_word_with_z(sentence);

    if (match != NULL) {
        if (printf("Matched word: %s\n", match) < 0) {
            free(match);
            return EXIT_FAILURE;
        }
        free(match);
        match = NULL;
    } else {
        if (printf("No word containing 'z' found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (word_contains_z("puzzle")) {
        if (printf("The word 'puzzle' contains 'z'\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}