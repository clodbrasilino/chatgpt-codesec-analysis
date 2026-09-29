#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

char* find_first_repeated_word(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LENGTH] = {0};
    int word_count = 0;
    const char *token;

    token = strtok((char *)str, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        for (int i = 0; i < word_count; ++i) {
            if (strcmp(words[i], token) == 0) {
                return strdup(token);
            }
        }
        size_t token_length;
        /* Possible weaknesses found:
         *  %n in format string (no. 2) requires 'int *' but the argument type is 'size_t * {aka unsigned long *}'. [invalidScanfArgType_int]
         * Flawfinder sscanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
         */
        if (sscanf(token, "%99s%n", words[word_count], &token_length) == 1) {
            words[word_count][token_length] = '\0';
            ++word_count;
        } else {
            return NULL;
        }
        token = strtok(NULL, " ");
    }

    return NULL;
}

int main() {
    const char *input = "This is a test to find the first repeated word in the string this is";
    char *result = find_first_repeated_word(input);

    if (result) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}