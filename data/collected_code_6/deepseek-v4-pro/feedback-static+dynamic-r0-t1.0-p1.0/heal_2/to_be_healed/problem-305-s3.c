#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50

int match_p_words(const char *word1, const char *word2) {
    if (word1 == NULL || word2 == NULL) {
        return 0;
    }
    if (word1[0] != 'p' && word1[0] != 'P') {
        return 0;
    }
    if (word2[0] != 'p' && word2[0] != 'P') {
        return 0;
    }
    return strcmp(word1, word2) == 0;
}

int main(void) {
    char **words = NULL;
    int word_count = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_WORD_LEN];
    int i;
    int found = 0;

    words = malloc(MAX_WORDS * sizeof(char *));
    if (words == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < MAX_WORDS; i++) {
        words[i] = NULL;
    }

    printf("Enter words starting with 'p' (type 'end' to finish):\n");

    while (word_count < MAX_WORDS) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "end") == 0) {
            break;
        }

        if (input[0] != 'p' && input[0] != 'P') {
            printf("Word must start with 'p'. Try again.\n");
            continue;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        words[word_count] = malloc(strlen(input) + 1);
        if (words[word_count] == NULL) {
            printf("Memory allocation failed.\n");
            break;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(words[word_count], input);
        word_count++;
    }

    if (word_count < 2) {
        printf("Not enough words to compare.\n");
        for (i = 0; i < word_count; i++) {
            free(words[i]);
        }
        free(words);
        return 1;
    }

    printf("\nMatching pairs of words starting with 'p':\n");
    for (i = 0; i < word_count - 1; i++) {
        int j;
        for (j = i + 1; j < word_count; j++) {
            if (match_p_words(words[i], words[j])) {
                printf("%s and %s match\n", words[i], words[j]);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No matching pairs found.\n");
    }

    for (i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}