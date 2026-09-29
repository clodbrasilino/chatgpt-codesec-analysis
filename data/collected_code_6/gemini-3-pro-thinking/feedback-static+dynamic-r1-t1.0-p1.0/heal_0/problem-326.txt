#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct WordCount {
    const char *word;
    size_t count;
};

const char *get_most_frequent_word(const char * const *words, size_t num_words);

const char *get_most_frequent_word(const char * const *words, size_t num_words) {
    if (!words || num_words == 0) {
        return NULL;
    }

    struct WordCount *counts = malloc(num_words * sizeof(struct WordCount));
    if (!counts) {
        return NULL;
    }

    size_t unique_words = 0;
    size_t max_count = 0;
    const char *most_frequent = NULL;

    for (size_t i = 0; i < num_words; i++) {
        if (!words[i]) {
            continue;
        }

        bool found = false;
        size_t current_count = 0;

        for (size_t j = 0; j < unique_words; j++) {
            if (strcmp(counts[j].word, words[i]) == 0) {
                counts[j].count++;
                current_count = counts[j].count;
                found = true;
                break;
            }
        }

        if (!found) {
            counts[unique_words].word = words[i];
            counts[unique_words].count = 1;
            current_count = 1;
            unique_words++;
        }

        if (current_count > max_count) {
            max_count = current_count;
            most_frequent = words[i];
        }
    }

    free(counts);

    return most_frequent;
}

int main(void) {
    const char *word_list[] = {
        "apple",
        "banana",
        "cherry",
        "apple",
        "date",
        "banana",
        "apple",
        "elderberry"
    };
    
    size_t num_words = sizeof(word_list) / sizeof(word_list[0]);

    const char *most_frequent = get_most_frequent_word(word_list, num_words);

    if (most_frequent) {
        printf("%s\n", most_frequent);
    } else {
        printf("No valid words found or memory allocation failed.\n");
    }

    return 0;
}