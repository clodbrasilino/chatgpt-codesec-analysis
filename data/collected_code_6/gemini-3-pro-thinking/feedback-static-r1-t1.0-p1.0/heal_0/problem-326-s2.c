#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct word_freq {
    const char *word;
    size_t count;
};

const char *get_most_frequent_word(const char *const *words, size_t num_words) {
    if (!words || num_words == 0) {
        return NULL;
    }

    struct word_freq *frequencies = calloc(num_words, sizeof(struct word_freq));
    if (!frequencies) {
        return NULL;
    }

    size_t unique_words = 0;
    const char *most_frequent = NULL;
    size_t max_count = 0;

    for (size_t i = 0; i < num_words; ++i) {
        if (!words[i]) {
            continue;
        }

        size_t j;
        for (j = 0; j < unique_words; ++j) {
            if (strcmp(frequencies[j].word, words[i]) == 0) {
                frequencies[j].count++;
                break;
            }
        }

        if (j == unique_words) {
            frequencies[unique_words].word = words[i];
            frequencies[unique_words].count = 1;
            unique_words++;
        }

        if (frequencies[j].count > max_count) {
            max_count = frequencies[j].count;
            most_frequent = frequencies[j].word;
        }
    }

    free(frequencies);
    return most_frequent;
}

int main(void) {
    const char *word_list[] = {
        "apple", "banana", "apple", "orange", "banana", "apple"
    };
    size_t count = sizeof(word_list) / sizeof(word_list[0]);

    const char *result = get_most_frequent_word(word_list, count);
    if (result) {
        printf("%s\n", result);
    } else {
        printf("No valid words found.\n");
    }

    return EXIT_SUCCESS;
}