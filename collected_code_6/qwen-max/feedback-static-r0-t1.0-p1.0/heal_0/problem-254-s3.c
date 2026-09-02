#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void findWordsStartingAorE(const char *input, char ***result, int *count) {
    const int MAX_WORD_LENGTH = 64;
    char **words = NULL;
    int wordsCount = 0;
    int capacity = 10;

    words = (char **)malloc(capacity * sizeof(char *));
    if (words == NULL) return;

    char *token = strtok((char *)input, " ");
    while (token != NULL) {
        if (strlen(token) > 0 && (token[0] == 'a' || token[0] == 'e')) {
            if (wordsCount >= capacity) {
                capacity *= 2;
                words = (char **)realloc(words, capacity * sizeof(char *));
                if (words == NULL) goto cleanup;
            }
            words[wordsCount] = (char *)malloc((strlen(token) + 1) * sizeof(char));
            if (words[wordsCount] == NULL) goto cleanup;
            strcpy(words[wordsCount], token);
            wordsCount++;
        }
        token = strtok(NULL, " ");
    }

    *result = words;
    *count = wordsCount;
    return;

cleanup:
    for (int i = 0; i < wordsCount; i++) {
        free(words[i]);
    }
    free(words);
    *result = NULL;
    *count = 0;
}

int main() {
    const char *input = "an apple a day keeps the doctor away everyone enjoys an early morning";
    char **result;
    int count;

    findWordsStartingAorE(input, &result, &count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}