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
    char *words[MAX_WORDS] = {NULL};
    int word_count = 0;

    const char *token;
    token = strtok((char *)input, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        if (!is_word_in_array(token, words, word_count)) {
            words[word_count++] = strdup(token);
        }
        token = strtok(NULL, " ");
    }

    size_t result_size = strlen(input) + 1;
    char *result = (char *)malloc(result_size);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    for (int i = 0; i < word_count; i++) {
        size_t remaining_space = result_size - strlen(result) - 1;
        strncat(result, words[i], remaining_space);
        remaining_space -= strlen(words[i]);
        if (remaining_space > 0) {
            strncat(result, " ", remaining_space);
        }
        free(words[i]);
    }

    if (strlen(result) > 0) {
        result[strlen(result) - 1] = '\0';
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