#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void findWordsStartingAorE(const char *input, char ***result, int *count) {
    /* Possible weaknesses found:
     *  Variable 'MAX_WORD_LENGTH' is assigned a value that is never used. [unreadVariable]
     */
    const int MAX_WORD_LENGTH = 64;
    char **words = NULL;
    int wordsCount = 0;
    int capacity = 10;

    words = (char **)malloc(capacity * sizeof(char *));
    if (words == NULL) return;

    char *inputCopy = strdup(input);
    char *token = strtok(inputCopy, " ");
    while (token != NULL) {
        if (strlen(token) > 0 && (token[0] == 'a' || token[0] == 'e')) {
            if (wordsCount >= capacity) {
                capacity *= 2;
                char **temp = (char **)realloc(words, capacity * sizeof(char *));
                if (temp == NULL) {
                    free(inputCopy);
                    for (int i = 0; i < wordsCount; i++) {
                        free(words[i]);
                    }
                    free(words);
                    *result = NULL;
                    *count = 0;
                    return;
                }
                words = temp;
            }
            words[wordsCount] = (char *)malloc((strlen(token) + 1) * sizeof(char));
            if (words[wordsCount] == NULL) {
                free(inputCopy);
                for (int i = 0; i < wordsCount; i++) {
                    free(words[i]);
                }
                free(words);
                *result = NULL;
                *count = 0;
                return;
            }
            strcpy(words[wordsCount], token);
            wordsCount++;
        }
        token = strtok(NULL, " ");
    }

    free(inputCopy);
    *result = words;
    *count = wordsCount;
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