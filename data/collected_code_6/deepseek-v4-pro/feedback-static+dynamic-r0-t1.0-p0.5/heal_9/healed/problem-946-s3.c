#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define MAX_UNIQUE_WORDS 1000

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

static void to_lowercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

static int find_word(const WordCount *words, int num_words, const char *word) {
    for (int i = 0; i < num_words; i++) {
        if (strcmp(words[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

static int add_word(WordCount *words, int *num_words, const char *word, int *max_count) {
    if (*num_words >= MAX_UNIQUE_WORDS) {
        return 0;
    }
    
    size_t len = strlen(word);
    if (len >= MAX_WORD_LEN) {
        len = MAX_WORD_LEN - 1;
    }
    
    memcpy(words[*num_words].word, word, len);
    words[*num_words].word[len] = '\0';
    words[*num_words].count = 1;
    (*num_words)++;
    
    if (words[*num_words - 1].count > *max_count) {
        *max_count = words[*num_words - 1].count;
    }
    
    return 1;
}

void find_most_common_elements(const char *text, WordCount *result, size_t result_capacity, int *result_count) {
    WordCount words[MAX_UNIQUE_WORDS];
    int num_words = 0;
    char current_word[MAX_WORD_LEN];
    int current_len = 0;
    int max_count = 0;

    memset(words, 0, sizeof(words));
    memset(current_word, 0, sizeof(current_word));

    for (size_t i = 0; text[i] != '\0'; i++) {
        if (isalnum((unsigned char)text[i])) {
            if (current_len < MAX_WORD_LEN - 1) {
                current_word[current_len] = (char)text[i];
                current_len++;
            }
        } else {
            if (current_len > 0) {
                current_word[current_len] = '\0';
                to_lowercase(current_word);

                int idx = find_word(words, num_words, current_word);
                if (idx >= 0) {
                    words[idx].count++;
                    if (words[idx].count > max_count) {
                        max_count = words[idx].count;
                    }
                } else {
                    add_word(words, &num_words, current_word, &max_count);
                }

                current_len = 0;
                current_word[0] = '\0';
            }
        }
    }

    if (current_len > 0) {
        current_word[current_len] = '\0';
        to_lowercase(current_word);

        int idx = find_word(words, num_words, current_word);
        if (idx >= 0) {
            words[idx].count++;
            if (words[idx].count > max_count) {
                max_count = words[idx].count;
            }
        } else {
            add_word(words, &num_words, current_word, &max_count);
        }
    }

    *result_count = 0;
    for (int i = 0; i < num_words && *result_count < (int)result_capacity; i++) {
        if (words[i].count == max_count) {
            if (*result_count < (int)result_capacity) {
                size_t word_len = strlen(words[i].word);
                if (word_len < MAX_WORD_LEN) {
                    memcpy(result[*result_count].word, words[i].word, word_len + 1);
                    result[*result_count].count = words[i].count;
                    (*result_count)++;
                }
            }
        }
    }
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog. The dog barks, and the fox runs away.";
    WordCount result[MAX_UNIQUE_WORDS];
    int result_count = 0;

    memset(result, 0, sizeof(result));

    find_most_common_elements(text, result, MAX_UNIQUE_WORDS, &result_count);

    printf("Most common elements:\n");
    for (int i = 0; i < result_count; i++) {
        printf("%s: %d\n", result[i].word, result[i].count);
    }

    return 0;
}