#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define MAX_UNIQUE_WORDS 1000

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

void to_lowercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

int find_word(const WordCount *words, int num_words, const char *word) {
    for (int i = 0; i < num_words; i++) {
        if (strcmp(words[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

int add_word(WordCount *words, int *num_words, const char *word, int *max_count) {
    if (*num_words >= MAX_UNIQUE_WORDS) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(word);
    if (len >= MAX_WORD_LEN) {
        len = MAX_WORD_LEN - 1;
    }
    
    if (len >= MAX_WORD_LEN) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char current_word[MAX_WORD_LEN];
    int current_len = 0;
    int max_count = 0;

    memset(words, 0, sizeof(words));
    memset(current_word, 0, sizeof(current_word));

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalnum((unsigned char)text[i])) {
            if (current_len < MAX_WORD_LEN - 1) {
                /* Possible weaknesses found:
                 *  Variable 'current_word[current_len]' is assigned a value that is never used. [unreadVariable]
                 */
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
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                if (strlen(words[i].word) < MAX_WORD_LEN) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(&result[*result_count], &words[i], sizeof(WordCount));
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