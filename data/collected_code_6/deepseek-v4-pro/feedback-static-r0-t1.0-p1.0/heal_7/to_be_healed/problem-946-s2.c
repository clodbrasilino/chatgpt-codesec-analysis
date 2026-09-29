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

int find_word(WordCount *words, int unique_count, const char *word) {
    for (int i = 0; i < unique_count; i++) {
        if (strcmp(words[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

size_t safe_word_copy(char *dest, const char *src, size_t dest_size) {
    if (dest_size == 0) {
        return 0;
    }
    
    size_t i;
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return i;
}

void find_most_common_elements(const char *text, WordCount *result, int *result_count) {
    if (text == NULL || result == NULL || result_count == NULL) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return;
    }
    
    WordCount words[MAX_UNIQUE_WORDS];
    int unique_count = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char current_word[MAX_WORD_LEN];
    int current_len = 0;
    int max_count = 0;
    int result_idx = 0;
    size_t text_len = 0;
    size_t i = 0;
    
    *result_count = 0;
    
    memset(words, 0, sizeof(words));
    memset(current_word, 0, sizeof(current_word));
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    text_len = strlen(text);
    
    for (i = 0; i < text_len; i++) {
        if (isalnum((unsigned char)text[i]) || text[i] == '_' || text[i] == '-') {
            if (current_len < MAX_WORD_LEN - 1) {
                current_word[current_len++] = text[i];
                current_word[current_len] = '\0';
            }
        } else {
            if (current_len > 0) {
                to_lowercase(current_word);
                
                int idx = find_word(words, unique_count, current_word);
                if (idx >= 0) {
                    words[idx].count++;
                } else if (unique_count < MAX_UNIQUE_WORDS) {
                    safe_word_copy(words[unique_count].word, current_word, MAX_WORD_LEN);
                    words[unique_count].count = 1;
                    unique_count++;
                }
                
                current_len = 0;
                memset(current_word, 0, sizeof(current_word));
            }
        }
    }
    
    if (current_len > 0) {
        to_lowercase(current_word);
        
        int idx = find_word(words, unique_count, current_word);
        if (idx >= 0) {
            words[idx].count++;
        } else if (unique_count < MAX_UNIQUE_WORDS) {
            safe_word_copy(words[unique_count].word, current_word, MAX_WORD_LEN);
            words[unique_count].count = 1;
            unique_count++;
        }
    }
    
    for (i = 0; i < (size_t)unique_count; i++) {
        if (words[i].count > max_count) {
            max_count = words[i].count;
        }
    }
    
    for (i = 0; i < (size_t)unique_count && result_idx < MAX_UNIQUE_WORDS; i++) {
        if (words[i].count == max_count) {
            safe_word_copy(result[result_idx].word, words[i].word, MAX_WORD_LEN);
            result[result_idx].count = words[i].count;
            result_idx++;
        }
    }
    
    *result_count = result_idx;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog. The dog barks, and the fox runs away. Quick brown fox!";
    WordCount results[MAX_UNIQUE_WORDS];
    int result_count = 0;
    
    memset(results, 0, sizeof(results));
    
    find_most_common_elements(text, results, &result_count);
    
    printf("Most common word(s):\n");
    for (int i = 0; i < result_count; i++) {
        printf("%s: %d\n", results[i].word, results[i].count);
    }
    
    return 0;
}