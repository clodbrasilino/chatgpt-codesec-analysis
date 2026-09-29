#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_WORD_LEN 101
#define MAX_UNIQUE_WORDS 1000

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

void to_lowercase(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }
    for (size_t i = 0; i < size && str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
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

size_t safe_word_copy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return 0;
    }
    
    size_t i;
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return i;
}

size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
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
    char current_word[MAX_WORD_LEN];
    size_t current_len = 0;
    int max_count = 0;
    int result_idx = 0;
    size_t text_len = 0;
    size_t i = 0;
    
    *result_count = 0;
    
    memset(words, 0, sizeof(words));
    memset(current_word, 0, sizeof(current_word));
    
    text_len = safe_strlen(text, SIZE_MAX);
    
    for (i = 0; i < text_len; i++) {
        if (isalnum((unsigned char)text[i]) || text[i] == '_' || text[i] == '-') {
            if (current_len < MAX_WORD_LEN - 1) {
                current_word[current_len++] = text[i];
                current_word[current_len] = '\0';
            }
        } else {
            if (current_len > 0) {
                to_lowercase(current_word, MAX_WORD_LEN);
                
                int idx = find_word(words, unique_count, current_word);
                if (idx >= 0) {
                    words[idx].count++;
                } else if (unique_count < MAX_UNIQUE_WORDS) {
                    safe_word_copy(words[unique_count].word, current_word, MAX_WORD_LEN);
                    words[unique_count].count = 1;
                    unique_count++;
                }
                
                current_len = 0;
                current_word[0] = '\0';
            }
        }
    }
    
    if (current_len > 0) {
        to_lowercase(current_word, MAX_WORD_LEN);
        
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