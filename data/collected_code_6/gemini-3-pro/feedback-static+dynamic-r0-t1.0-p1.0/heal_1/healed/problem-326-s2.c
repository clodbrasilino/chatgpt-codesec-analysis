#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 256

typedef struct {
    char *word;
    int count;
} WordCount;

char* get_most_frequent_word(char **strings, int num_strings) {
    if (strings == NULL || num_strings <= 0) {
        return NULL;
    }

    WordCount *word_counts = NULL;
    int num_unique_words = 0;

    for (int i = 0; i < num_strings; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        size_t len = strnlen(strings[i], MAX_WORD_LENGTH);
        if (len == 0 || len == MAX_WORD_LENGTH) {
            continue;
        }

        int found = 0;
        for (int j = 0; j < num_unique_words; j++) {
            if (strncmp(word_counts[j].word, strings[i], MAX_WORD_LENGTH) == 0) {
                word_counts[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            WordCount *temp = realloc(word_counts, (num_unique_words + 1) * sizeof(WordCount));
            if (temp == NULL) {
                for (int j = 0; j < num_unique_words; j++) {
                    free(word_counts[j].word);
                }
                free(word_counts);
                return NULL;
            }
            word_counts = temp;
            
            word_counts[num_unique_words].word = strndup(strings[i], MAX_WORD_LENGTH - 1);
            if (word_counts[num_unique_words].word == NULL) {
                for (int j = 0; j < num_unique_words; j++) {
                    free(word_counts[j].word);
                }
                free(word_counts);
                return NULL;
            }
            word_counts[num_unique_words].count = 1;
            num_unique_words++;
        }
    }

    if (num_unique_words == 0) {
        free(word_counts);
        return NULL;
    }

    int max_count = 0;
    char *most_frequent_word = NULL;

    for (int i = 0; i < num_unique_words; i++) {
        if (word_counts[i].count > max_count) {
            max_count = word_counts[i].count;
            most_frequent_word = word_counts[i].word;
        }
    }

    char *result = NULL;
    if (most_frequent_word != NULL) {
        result = strdup(most_frequent_word);
    }

    for (int i = 0; i < num_unique_words; i++) {
        free(word_counts[i].word);
    }
    free(word_counts);

    return result;
}

int main(void) {
    char *strings[] = {
        "apple",
        "banana",
        "apple",
        "orange",
        "banana",
        "apple",
        "grape"
    };
    int num_strings = sizeof(strings) / sizeof(strings[0]);

    char *most_frequent = get_most_frequent_word(strings, num_strings);

    if (most_frequent != NULL) {
        printf("%s\n", most_frequent);
        free(most_frequent);
    } 

    return 0;
}