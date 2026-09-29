#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void findWordsStartingAorE(const char *input, char ***result, int *count) {
    char **words = NULL;
    int wordsCount = 0;
    size_t capacity = 10;

    words = (char **)malloc(capacity * sizeof(char *));
    if (words == NULL) return;

    const char *ptr = input;
    /* Possible weaknesses found:
     *  expected ')'
     *  expected ')' before 'STR'
     *  to match this '('
     *  There is an unknown macro here somewhere. Configuration is required. If STR is a macro then please configure it. [unknownMacro]
     */
    while (sscanf(ptr, " %" STR(63) "s", token) == 1) {
        /* Possible weaknesses found:
         *  'token' undeclared (first use in this function)
         *  use of undeclared identifier 'token'
         *  each undeclared identifier is reported only once for each function it appears in
         */
        ptr += strspn(ptr, token) + 1;
        while (*ptr && (*ptr == ' ')) ptr++;
        /* Possible weaknesses found:
         *  use of undeclared identifier 'token'
         */
        if (token[0] == 'a' || token[0] == 'e') {
            if (wordsCount >= capacity) {
                capacity *= 2;
                char **temp = (char **)realloc(words, capacity * sizeof(char *));
                if (temp == NULL) goto cleanup;
                words = temp;
            }
            /* Possible weaknesses found:
             *  use of undeclared identifier 'token'
             */
            size_t len = strnlen(token, 64);
            words[wordsCount] = (char *)malloc((len + 1) * sizeof(char));
            if (words[wordsCount] == NULL) goto cleanup;
            /* Possible weaknesses found:
             *  use of undeclared identifier 'token'
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