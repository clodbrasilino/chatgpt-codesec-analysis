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

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

void to_lowercase(char *str, size_t max_len) {
    for (size_t i = 0; i < max_len && str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

int find_word(const WordCount *words, int unique_count, const char *word) {
    for (int i = 0; i < unique_count; i++) {
        if (strcmp(words[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

void safe_word_copy(char *dest, const char *src, size_t dest_size) {
    size_t len = safe_strlen(src, dest_size - 1);
    if (len >= dest_size) {
        len = dest_size - 1;
    }
    memcpy(dest, src, len);
    dest[len] = '\0';
}

void find_most_common_elements(const char *text, WordCount *result, int *result_count) {
    WordCount words[MAX_UNIQUE_WORDS];
    int unique_count = 0;
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
    
    text_len = safe_strlen(text, (size_t)-1);
    memset(words, 0, sizeof(words));
    *result_count = 0;
    
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
                    safe_word_copy(words[unique_count].word, current_word, MAX_WORD_LEN);
                    words[unique_count].count = 1;
                    unique_count++;
                } else {
                    fprintf(stderr, "Warning: maximum unique words limit reached\n");
                    current_len = 0;
                    continue;
                }
                
                current_len = 0;
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
            safe_word_copy(words[unique_count].word, current_word, MAX_WORD_LEN);
            words[unique_count].count = 1;
            unique_count++;
        }
    }
    
    for (int i = 0; i < unique_count; i++) {
        if (words[i].count > max_count) {
            max_count = words[i].count;
        }
    }
    
    for (int i = 0; i < unique_count && result_idx < MAX_UNIQUE_WORDS; i++) {
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
    
    find_most_common_elements(text, results, &result_count);
    
    printf("Most common word(s):\n");
    for (int i = 0; i < result_count; i++) {
        printf("%s: %d\n", results[i].word, results[i].count);
    }
    
    return 0;
}