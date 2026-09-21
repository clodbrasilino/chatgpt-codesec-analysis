#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void findWordsStartingAorE(const char *input, char ***result, int *count) {
    char **words = NULL;
    int wordsCount = 0;
    size_t capacity = 10;

    words = (char **)malloc(capacity * sizeof(char *));
    if (words == NULL) return;

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[64];
    const char *ptr = input;

    /* Possible weaknesses found:
     * Flawfinder sscanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    while (sscanf(ptr, " %63s", token) == 1) {
        ptr += strspn(ptr, token);
        /* Possible weaknesses found:
         *  Redundant condition: The condition '*ptr' is redundant since '*ptr == ' '' is sufficient. [redundantCondition]
         */
        while (*ptr && (*ptr == ' ')) ptr++;
        if (token[0] == 'a' || token[0] == 'e') {
            if (wordsCount >= capacity) {
                capacity *= 2;
                char **temp = (char **)realloc(words, capacity * sizeof(char *));
                if (temp == NULL) goto cleanup;
                words = temp;
            }
            size_t len = strnlen(token, 64);
            words[wordsCount] = (char *)malloc((len + 1) * sizeof(char));
            if (words[wordsCount] == NULL) goto cleanup;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
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