#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_WORD_LEN 101
#define MAX_UNIQUE_WORDS 1000

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    if (str == NULL) {
        return 0;
    }
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

void to_lowercase(char *str, size_t max_len) {
    if (str == NULL) {
        return;
    }
    for (size_t i = 0; i < max_len && str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

int find_word(const WordCount *words, int unique_count, const char *word) {
    if (words == NULL || word == NULL || unique_count <= 0) {
        return -1;
    }
    for (int i = 0; i < unique_count; i++) {
        if (strcmp(words[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

int safe_word_copy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return -1;
    }
    
    size_t src_len = safe_strlen(src, dest_size);
    if (src_len >= dest_size) {
        dest[0] = '\0';
        return -1;
    }
    
    size_t copy_len = src_len < dest_size - 1 ? src_len : dest_size - 1;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, copy_len);
    dest[copy_len] = '\0';
    return 0;
}

void find_most_common_elements(const char *text, WordCount *result, int *result_count) {
    WordCount words[MAX_UNIQUE_WORDS];
    int unique_count = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char current_word[MAX_WORD_LEN];
    size_t current_len = 0;
    int max_count = 0;
    int result_idx = 0;
    size_t text_len;
    
    if (text == NULL || result == NULL || result_count == NULL) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return;
    }
    
    text_len = safe_strlen(text, SIZE_MAX);
    memset(words, 0, sizeof(words));
    *result_count = 0;
    memset(current_word, 0, sizeof(current_word));
    
    for (size_t i = 0; i < text_len; i++) {
        if (isalnum((unsigned char)text[i]) || text[i] == '_' || text[i] == '-') {
            if (current_len < MAX_WORD_LEN - 1) {
                current_word[current_len++] = text[i];
            }
        } else {
            if (current_len > 0) {
                current_word[current_len] = '\0';
                to_lowercase(current_word, MAX_WORD_LEN);
                
                int idx = find_word(words, unique_count, current_word);
                if (idx >= 0) {
                    words[idx].count++;
                } else if (unique_count < MAX_UNIQUE_WORDS) {
                    if (safe_word_copy(words[unique_count].word, current_word, MAX_WORD_LEN) == 0) {
                        words[unique_count].count = 1;
                        unique_count++;
                    }
                } else {
                    fprintf(stderr, "Warning: maximum unique words limit reached\n");
                }
                
                current_len = 0;
                memset(current_word, 0, sizeof(current_word));
            }
        }
    }
    
    if (current_len > 0) {
        current_word[current_len] = '\0';
        to_lowercase(current_word, MAX_WORD_LEN);
        
        int idx = find_word(words, unique_count, current_word);
        if (idx >= 0) {
            words[idx].count++;
        } else if (unique_count < MAX_UNIQUE_WORDS) {
            if (safe_word_copy(words[unique_count].word, current_word, MAX_WORD_LEN) == 0) {
                words[unique_count].count = 1;
                unique_count++;
            }
        }
    }
    
    for (int i = 0; i < unique_count; i++) {
        if (words[i].count > max_count) {
            max_count = words[i].count;
        }
    }
    
    for (int i = 0; i < unique_count && result_idx < MAX_UNIQUE_WORDS; i++) {
        if (words[i].count == max_count) {
            if (safe_word_copy(result[result_idx].word, words[i].word, MAX_WORD_LEN) == 0) {
                result[result_idx].count = words[i].count;
                result_idx++;
            }
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