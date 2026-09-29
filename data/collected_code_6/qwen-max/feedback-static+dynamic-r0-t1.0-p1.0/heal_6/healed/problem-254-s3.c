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

    char token[MAX_WORD_LENGTH];
    const char *ptr = input;

    while (sscanf(ptr, " %63s", token) == 1) {
        ptr += strspn(ptr, token);
        while (*ptr && (*ptr == ' ')) ptr++;
        if (token[0] == 'a' || token[0] == 'e') {
            if (wordsCount >= capacity) {
                capacity *= 2;
                char **temp = (char **)realloc(words, capacity * sizeof(char *));
                if (temp == NULL) goto cleanup;
                words = temp;
            }
            size_t len = strnlen(token, MAX_WORD_LENGTH);
            words[wordsCount] = (char *)malloc((len + 1) * sizeof(char));
            if (words[wordsCount] == NULL) goto cleanup;
            memcpy(words[wordsCount], token, len);
            words[wordsCount][len] = '\0';
            wordsCount++;
        }
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