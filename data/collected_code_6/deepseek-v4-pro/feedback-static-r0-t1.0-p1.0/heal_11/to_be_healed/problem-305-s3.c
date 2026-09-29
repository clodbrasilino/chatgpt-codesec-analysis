#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50
#define MAX_INPUT_LEN 256

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
    char (*words)[MAX_WORD_LEN] = malloc(MAX_WORDS * sizeof(char[MAX_WORD_LEN]));
    if (words == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    int word_count = 0;
    int found = 0;
    size_t i;

    printf("Enter words starting with 'p' (type 'end' to finish):\n");

    while (word_count < MAX_WORDS) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char input[MAX_INPUT_LEN];
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        size_t input_len = strnlen(input, sizeof(input));
        /* Possible weaknesses found:
         *  Assuming that condition 'input_len==0' is not redundant
         */
        if (input_len == 0 || (input_len == 1 && input[0] == '\n')) {
            continue;
        }

        /* Possible weaknesses found:
         *  Condition 'input_len>0' is always true [knownConditionTrueFalse]
         *  Condition 'input_len>0' is always true
         */
        if (input_len > 0 && input[input_len - 1] == '\n') {
            input[input_len - 1] = '\0';
            input_len--;
        } else {
            if (input_len >= sizeof(input) - 1) {
                int c;
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                while ((c = getchar()) != '\n' && c != EOF) {
                }
                printf("Input too long. Try again.\n");
                if (c == EOF) {
                    clearerr(stdin);
                }
                continue;
            }
        }

        if (input_len >= MAX_WORD_LEN) {
            printf("Word too long. Try again.\n");
            continue;
        }

        if (input_len == 3 && strncmp(input, "end", 3) == 0) {
            break;
        }

        if (input_len == 0 || (input[0] != 'p' && input[0] != 'P')) {
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
        free(words);
        return 1;
    }

    printf("\nMatching pairs of words starting with 'p':\n");
    for (i = 0; i < (size_t)word_count - 1; i++) {
        size_t j;
        for (j = i + 1; j < (size_t)word_count; j++) {
            if (match_p_words(words[i], words[j])) {
                printf("%s and %s match\n", words[i], words[j]);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No matching pairs found.\n");
    }

    free(words);
    return 0;
}