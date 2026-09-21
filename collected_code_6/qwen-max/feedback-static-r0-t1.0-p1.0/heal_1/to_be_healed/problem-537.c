#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char* find_first_repeated_word(const char* str) {
    const int MAX_WORDS = 100;
    const int MAX_WORD_LENGTH = 50;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int word_count = 0;

    const char* token = strtok((char*)str, " ");
    while (token && word_count < MAX_WORDS) {
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                return token;
            }
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(words[word_count++], token);
        token = strtok(NULL, " ");
    }

    return NULL;
}

int main() {
    const char* input = "This is a test string with test words";
    char* result = find_first_repeated_word(input);
    if (result != NULL) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated words found.\n");
    }
    return 0;
}