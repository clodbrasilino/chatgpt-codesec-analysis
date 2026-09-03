#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

/* Possible weaknesses found:
 *  Parameter 'strings' can be declared as const array [constParameter]
 */
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

        char *temp = (char *)malloc(strlen(strings[i]) + 1);
        if (temp == NULL) {
            free(words);
            return NULL;
        }
        strcpy(temp, strings[i]);

        char *token = strtok(temp, " \t\n\r.,;:!?\"'()[]{}");
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

        free(temp);
    }

    free(words);
    return result;
}

int main(void) {
    char *strings[] = {
        "hello world hello",
        "this is a test",
        "hello again world",
        "test test test"
    };
    int n = sizeof(strings) / sizeof(strings[0]);

    char *result = most_frequent_word(strings, n);
    if (result != NULL) {
        /* Possible weaknesses found:
         * ASan: heap-use-after-free
         */
        printf("Most frequent word: %s\n", result);
    } else {
        printf("No words found\n");
    }

    return 0;
}