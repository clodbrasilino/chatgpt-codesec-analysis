#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 256

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

char* get_most_frequent_word(const char** strings, int num_strings) {
    if (strings == NULL || num_strings <= 0) {
        return NULL;
    }

    WordCount* word_counts = calloc(num_strings, sizeof(WordCount));
    if (word_counts == NULL) {
        return NULL;
    }

    int unique_words = 0;
    int max_count = 0;
    char* most_frequent = NULL;

    for (int i = 0; i < num_strings; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        int found = 0;
        for (int j = 0; j < unique_words; j++) {
            if (strncmp(word_counts[j].word, strings[i], MAX_WORD_LEN - 1) == 0) {
                word_counts[j].count++;
                if (word_counts[j].count > max_count) {
                    max_count = word_counts[j].count;
                    most_frequent = word_counts[j].word;
                }
                found = 1;
                break;
            }
        }

        if (!found && unique_words < num_strings) {
            strncpy(word_counts[unique_words].word, strings[i], MAX_WORD_LEN - 1);
            word_counts[unique_words].word[MAX_WORD_LEN - 1] = '\0';
            word_counts[unique_words].count = 1;
            
            if (1 > max_count) {
                max_count = 1;
                most_frequent = word_counts[unique_words].word;
            }
            unique_words++;
        }
    }

    char* result = NULL;
    if (most_frequent != NULL) {
        result = strdup(most_frequent);
    }

    free(word_counts);
    return result;
}

int main() {
    const char* strings[] = {
        "apple", "banana", "apple", "orange", 
        "banana", "apple", "grape", "banana", 
        "banana"
    };
    int num_strings = sizeof(strings) / sizeof(strings[0]);

    char* most_frequent = get_most_frequent_word(strings, num_strings);
    
    if (most_frequent != NULL) {
        printf("%s\n", most_frequent);
        free(most_frequent);
    } else {
        printf("Error or no valid words found.\n");
    }

    return 0;
}