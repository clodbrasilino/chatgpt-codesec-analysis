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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LEN];
    int word_count = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_WORD_LEN];
    int i;
    int found = 0;

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
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(words[word_count], input, MAX_WORD_LEN - 1);
        words[word_count][MAX_WORD_LEN - 1] = '\0';
        word_count++;
    }

    if (word_count < 2) {
        printf("Not enough words to compare.\n");
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

    return 0;
}