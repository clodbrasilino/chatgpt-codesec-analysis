#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50

bool match_words_starting_with_p(const char words[][MAX_WORD_LEN], int count,
                                 char *first_match, char *second_match, size_t buffer_size) {
    if (words == NULL || first_match == NULL || second_match == NULL ||
        buffer_size == 0 || count < 2 || count > MAX_WORDS) {
        return false;
    }

    if (buffer_size < MAX_WORD_LEN) {
        return false;
    }

    int found = 0;

    for (int i = 0; i < count && found < 2; i++) {
        if (words[i][0] == 'p') {
            size_t len = strnlen(words[i], MAX_WORD_LEN);
            if (len >= buffer_size) {
                return false;
            }

            if (found == 0) {
                snprintf(first_match, buffer_size, "%s", words[i]);
                found++;
            } else {
                snprintf(second_match, buffer_size, "%s", words[i]);
                found++;
            }
        }
    }

    return found == 2;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word_list[MAX_WORDS][MAX_WORD_LEN] = {
        "apple", "pear", "peach", "banana",
        "plum", "orange", "pineapple", "grape"
    };
    int word_count = 8;
    
    char *first_word = calloc(MAX_WORD_LEN, sizeof(char));
    if (first_word == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    char *second_word = calloc(MAX_WORD_LEN, sizeof(char));
    if (second_word == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_word);
        return 1;
    }

    if (match_words_starting_with_p(word_list, word_count,
                                    first_word, second_word, MAX_WORD_LEN)) {
        printf("First match: %s\n", first_word);
        printf("Second match: %s\n", second_word);
    } else {
        printf("Could not find two words starting with 'p'\n");
    }

    free(first_word);
    free(second_word);

    return 0;
}