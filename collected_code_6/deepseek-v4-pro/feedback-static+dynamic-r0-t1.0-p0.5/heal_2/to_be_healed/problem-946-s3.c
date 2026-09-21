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
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int find_word(WordCount *words, int num_words, const char *word) {
    for (int i = 0; i < num_words; i++) {
        if (strcmp(words[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

void find_most_common_elements(const char *text, WordCount *result, int *result_count) {
    WordCount words[MAX_UNIQUE_WORDS];
    int num_words = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char current_word[MAX_WORD_LEN];
    int current_len = 0;
    int max_count = 0;
    
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalnum((unsigned char)text[i])) {
            if (current_len < MAX_WORD_LEN - 1) {
                current_word[current_len++] = text[i];
            }
        } else {
            if (current_len > 0) {
                current_word[current_len] = '\0';
                to_lowercase(current_word);
                
                int idx = find_word(words, num_words, current_word);
                if (idx >= 0) {
                    words[idx].count++;
                } else if (num_words < MAX_UNIQUE_WORDS) {
                    /* Possible weaknesses found:
                     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                     */
                    strncpy(words[num_words].word, current_word, MAX_WORD_LEN - 1);
                    words[num_words].word[MAX_WORD_LEN - 1] = '\0';
                    words[num_words].count = 1;
                    num_words++;
                }
                
                if (idx >= 0 && words[idx].count > max_count) {
                    max_count = words[idx].count;
                } else if (idx < 0 && num_words > 0 && words[num_words - 1].count > max_count) {
                    max_count = words[num_words - 1].count;
                }
                
                current_len = 0;
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
        } else if (num_words < MAX_UNIQUE_WORDS) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(words[num_words].word, current_word, MAX_WORD_LEN - 1);
            words[num_words].word[MAX_WORD_LEN - 1] = '\0';
            words[num_words].count = 1;
            num_words++;
            if (num_words > 0 && words[num_words - 1].count > max_count) {
                max_count = words[num_words - 1].count;
            }
        }
    }
    
    *result_count = 0;
    for (int i = 0; i < num_words; i++) {
        /* Possible weaknesses found:
         *  Uninitialized variable: words.count [uninitvar]
         *  Uninitialized variable: words.count
         */
        if (words[i].count == max_count) {
            result[*result_count] = words[i];
            (*result_count)++;
        }
    }
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog. The dog barks, and the fox runs away.";
    WordCount result[MAX_UNIQUE_WORDS];
    int result_count = 0;
    
    find_most_common_elements(text, result, &result_count);
    
    printf("Most common elements:\n");
    for (int i = 0; i < result_count; i++) {
        printf("%s: %d\n", result[i].word, result[i].count);
    }
    
    return 0;
}