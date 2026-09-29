#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

char *most_frequent_word(char *strings[], int n) {
    if (n <= 0 || strings == NULL) {
        return NULL;
    }

    WordCount *words = (WordCount *)malloc(MAX_WORDS * sizeof(WordCount));
    if (words == NULL) {
        return NULL;
    }

    int word_count = 0;
    int max_count = 0;
    char *result = NULL;

    for (int i = 0; i < n; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        /* Possible weaknesses found:
         * ASan: BUS
         */
        char *token = strtok(strings[i], " \t\n\r.,;:!?\"'()[]{}");
        while (token != NULL) {
            int found = 0;
            for (int j = 0; j < word_count; j++) {
                if (strcmp(words[j].word, token) == 0) {
                    words[j].count++;
                    if (words[j].count > max_count) {
                        max_count = words[j].count;
                        result = words[j].word;
                    }
                    found = 1;
                    break;
                }
            }

            if (!found && word_count < MAX_WORDS) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(words[word_count].word, token, MAX_WORD_LEN - 1);
                words[word_count].word[MAX_WORD_LEN - 1] = '\0';
                words[word_count].count = 1;
                if (words[word_count].count > max_count) {
                    max_count = words[word_count].count;
                    result = words[word_count].word;
                }
                word_count++;
            }

            token = strtok(NULL, " \t\n\r.,;:!?\"'()[]{}");
        }
    }

    char *final_result = NULL;
    if (result != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        final_result = (char *)malloc(strlen(result) + 1);
        if (final_result != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(final_result, result);
        }
    }

    free(words);
    return final_result;
}

int main(void) {
    char *test_strings[] = {
        "hello world hello",
        "this is a test",
        "hello again world",
        "test test test"
    };

    char *result = most_frequent_word(test_strings, 4);
    if (result != NULL) {
        printf("Most frequent word: %s\n", result);
        free(result);
    } else {
        printf("No words found\n");
    }

    return 0;
}