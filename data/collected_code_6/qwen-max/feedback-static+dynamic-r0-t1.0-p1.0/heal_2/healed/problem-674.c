#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LENGTH 64

int is_word_in_array(const char *word, const char **words, int num_words) {
    for (int i = 0; i < num_words; ++i) {
        if (strcmp(word, words[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

char *remove_duplicate_words(const char *input) {
    size_t input_len = strlen(input);
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int num_words = 0;

    const char *p = input;

    while (*p) {
        while (*p && !isalnum((unsigned char)*p)) p++;
        const char *word_start = p;
        while (*p && isalnum((unsigned char)*p)) p++;

        if (word_start != p && !is_word_in_array(word_start, (const char *const *)words, num_words)) {
            if (num_words >= MAX_WORDS) {
                free(result);
                return NULL;
            }
            size_t word_len = p - word_start;
            if (word_len < MAX_WORD_LENGTH) {
                strncpy(words[num_words], word_start, word_len);
                words[num_words][word_len] = '\0';
                strncat(result, word_start, word_len);
                strncat(result, " ", 1);
                num_words++;
            }
        }

        while (*p && !isalnum((unsigned char)*p)) p++;
    }
    result[strlen(result) - 1] = '\0';

    return result;
}

int main() {
    const char *input = "this this is a test test of a duplicate remover";
    char *output = remove_duplicate_words(input);

    if (output == NULL) {
        fprintf(stderr, "Error: Memory allocation failed or too many unique words.\n");
        return 1;
    }

    printf("Original: %s\n", input);
    printf("Processed: %s\n", output);

    free(output);
    return 0;
}