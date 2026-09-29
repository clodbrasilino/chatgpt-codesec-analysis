#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LENGTH 64

int is_word_in_array(const char *word, const char *words[], int num_words) {
    for (int i = 0; i < num_words; ++i) {
        if (strcmp(word, words[i]) == 0) return 1;
    }
    return 0;
}

char *strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *result = (char *)malloc(len);
    if (result) memcpy(result, s, len);
    return result;
}

char *remove_duplicate_words(const char *input) {
    char *result = (char *)malloc(strlen(input) + 1);
    if (!result) return NULL;

    char *words[MAX_WORDS];
    int num_words = 0;

    const char *p = input;
    result[0] = '\0';

    while (*p) {
        while (*p && !isalnum((unsigned char)*p)) p++;
        const char *word_start = p;

        while (*p && isalnum((unsigned char)*p)) p++;

        int word_len = p - word_start;
        if (word_len > 0) {
            char *word_copy = (char *)malloc(word_len + 1);
            if (!word_copy) {
                free(result);
                return NULL;
            }
            strncpy(word_copy, word_start, word_len);
            word_copy[word_len] = '\0';

            if (!is_word_in_array(word_copy, words, num_words)) {
                if (num_words >= MAX_WORDS) {
                    free(result);
                    free(word_copy);
                    return NULL;
                }
                words[num_words++] = word_copy;
                strncat(result, word_copy, word_len);
                strncat(result, " ", 1);
            } else {
                free(word_copy);
            }
        }
    }
    if (strlen(result) > 0) result[strlen(result) - 1] = '\0';
    
    for (int i = 0; i < num_words; ++i) free(words[i]);

    return result;
}

int main() {
    const char *input = "Python Exercises Practice Solution";
    char *output = remove_duplicate_words(input);

    if (!output) {
        fprintf(stderr, "Error: Memory allocation failed or too many unique words.\n");
        return 1;
    }

    printf("Original: %s\n", input);
    printf("Processed: %s\n", output);

    free(output);
    return 0;
}