#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

int is_word_in_array(const char *word, const char *const array[], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(word, array[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

char* remove_duplicates(const char *input) {
    char **words = malloc(MAX_WORDS * sizeof(char *));
    if (words == NULL) {
        return NULL;
    }
    for (int i = 0; i < MAX_WORDS; i++) {
        words[i] = NULL;
    }

    int word_count = 0;

    const char *token;
    token = strtok((char *)input, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        if (!is_word_in_array(token, words, word_count)) {
            words[word_count] = strdup(token);
            if (words[word_count] == NULL) {
                for (int i = 0; i < word_count; i++) {
                    free(words[i]);
                }
                free(words);
                return NULL;
            }
            word_count++;
        }
        token = strtok(NULL, " ");
    }

    size_t input_len = strlen(input);
    char *result = malloc(input_len + 1);
    if (result == NULL) {
        for (int i = 0; i < word_count; i++) {
            free(words[i]);
        }
        free(words);
        return NULL;
    }
    result[0] = '\0';

    size_t result_len = 0;
    for (int i = 0; i < word_count; i++) {
        size_t len = strlen(words[i]);
        if (result_len + len + 1 <= input_len + 1) {
            strncat(result, words[i], len);
            result_len += len;
            strncat(result, " ", 1);
            result_len += 1;
        }
        free(words[i]);
    }

    if (result_len > 0) {
        result[result_len - 1] = '\0';
    }

    free(words);
    return result;
}

int main() {
    const char *input = "this this is a test test string with with duplicates";
    char *output = remove_duplicates(input);
    if (output) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}