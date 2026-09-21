#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

int is_word_in_array(const char *word, const char *array[], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(word, array[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

char* remove_duplicates(const char *input) {
    const char *words[MAX_WORDS] = {NULL};
    int word_count = 0;

    char *input_copy = strdup(input);
    if (input_copy == NULL) {
        return NULL;
    }

    char *token = strtok(input_copy, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        if (!is_word_in_array(token, (const char **)words, word_count)) {
            size_t len = strlen(token);
            if (len <= MAX_WORD_LENGTH) {
                words[word_count] = strndup(token, len);
                if (words[word_count] == NULL) {
                    free(input_copy);
                    for (int i = 0; i < word_count; i++) {
                        free(words[i]);
                    }
                    return NULL;
                }
                word_count++;
            }
        }
        token = strtok(NULL, " ");
    }

    free(input_copy);

    size_t output_length = 0;
    for (int i = 0; i < word_count; i++) {
        output_length += strlen(words[i]) + 1;
    }

    char *result = (char *)malloc(output_length + 1);
    if (result == NULL) {
        for (int i = 0; i < word_count; i++) {
            free(words[i]);
        }
        return NULL;
    }
    *result = '\0';

    for (int i = 0; i < word_count; i++) {
        strncat(result, words[i], output_length - strlen(result));
        if (i < word_count - 1) {
            strncat(result, " ", output_length - strlen(result));
        }
        free(words[i]);
    }

    return result;
}

int main() {
    const char *input = "this this is a test test string with with duplicates";
    char *output = remove_duplicates(input);
    printf("%s\n", output);
    free(output);
    return 0;
}