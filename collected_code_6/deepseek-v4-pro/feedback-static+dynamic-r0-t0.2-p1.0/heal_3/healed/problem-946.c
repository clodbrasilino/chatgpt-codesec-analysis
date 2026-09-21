#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_WORD_LEN 100
#define MAX_UNIQUE_WORDS 1000

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

static int find_word(WordCount *words, int num_words, const char *word) {
    for (int i = 0; i < num_words; i++) {
        if (strcmp(words[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

static void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

static size_t safe_strlen(const char *str) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < SIZE_MAX && str[len] != '\0') {
        len++;
    }
    return len;
}

void find_most_common_elements(const char *text) {
    if (text == NULL) {
        fprintf(stderr, "Error: NULL text input\n");
        return;
    }

    WordCount *words = calloc(MAX_UNIQUE_WORDS, sizeof(WordCount));
    if (words == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return;
    }

    int num_words = 0;
    char current_word[MAX_WORD_LEN];
    int word_len = 0;
    size_t text_len = safe_strlen(text);

    for (size_t i = 0; i <= text_len; i++) {
        char c = text[i];
        
        if (isalnum((unsigned char)c)) {
            if (word_len < MAX_WORD_LEN - 1) {
                current_word[word_len++] = c;
            }
        } else {
            if (word_len > 0) {
                current_word[word_len] = '\0';
                to_lowercase(current_word);
                
                int idx = find_word(words, num_words, current_word);
                if (idx >= 0) {
                    words[idx].count++;
                } else if (num_words < MAX_UNIQUE_WORDS) {
                    size_t copy_len = (size_t)word_len < MAX_WORD_LEN ? (size_t)word_len : MAX_WORD_LEN - 1;
                    if (copy_len >= MAX_WORD_LEN) {
                        copy_len = MAX_WORD_LEN - 1;
                    }
                    memcpy(words[num_words].word, current_word, copy_len);
                    words[num_words].word[copy_len] = '\0';
                    words[num_words].count = 1;
                    num_words++;
                }
                word_len = 0;
            }
        }
    }

    if (num_words == 0) {
        printf("No words found in text.\n");
        free(words);
        return;
    }

    int max_count = 0;
    for (int i = 0; i < num_words; i++) {
        if (words[i].count > max_count) {
            max_count = words[i].count;
        }
    }

    printf("Most common elements (count: %d):\n", max_count);
    for (int i = 0; i < num_words; i++) {
        if (words[i].count == max_count) {
            printf("  %s: %d\n", words[i].word, words[i].count);
        }
    }

    free(words);
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog. The dog barks, and the fox runs away. Fox and dog are friends.";
    
    printf("Analyzing text:\n%s\n\n", text);
    find_most_common_elements(text);
    
    return 0;
}