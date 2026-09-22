#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 256
#define MAX_WORD_LEN 64
#define MAX_ADVERB_LEN 32
#define SENTENCE_BUFFER_SIZE 4096

typedef struct {
    char word[MAX_WORD_LEN];
    int position;
} AdverbInfo;

static const char *adverb_suffixes[] = {
    "ly",
    "wise",
    "wards",
    "where",
    "when",
    "how",
    "why",
    NULL
};

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    if (str == NULL) {
        return 0;
    }
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static int ends_with(const char *str, size_t str_len, const char *suffix) {
    size_t suffix_len;
    
    if (str == NULL || suffix == NULL) {
        return 0;
    }
    
    suffix_len = safe_strlen(suffix, MAX_ADVERB_LEN);
    
    if (str_len < suffix_len) {
        return 0;
    }
    
    if (suffix_len == 0) {
        return 0;
    }
    
    return strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0;
}

static int is_adverb(const char *word) {
    int i;
    size_t len;
    
    if (word == NULL) {
        return 0;
    }
    
    len = safe_strlen(word, MAX_ADVERB_LEN);
    
    if (len < 2 || len >= MAX_ADVERB_LEN) {
        return 0;
    }
    
    if (isupper((unsigned char)word[0])) {
        return 0;
    }
    
    for (i = 0; adverb_suffixes[i] != NULL; i++) {
        if (ends_with(word, len, adverb_suffixes[i])) {
            if (strcmp(word, "family") == 0 || strcmp(word, "rely") == 0 ||
                strcmp(word, "apply") == 0 || strcmp(word, "supply") == 0) {
                continue;
            }
            return 1;
        }
    }
    
    return 0;
}

static void to_lowercase(char *str, size_t size) {
    size_t i;
    if (str == NULL) {
        return;
    }
    for (i = 0; i < size && str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

static int find_adverbs(const char *sentence, AdverbInfo *adverbs, int max_adverbs) {
    char *buffer;
    char *token;
    const char *delimiters = " \t\n\r.,;:!?\"'()[]{}";
    int count = 0;
    int position = 0;
    char *saveptr;
    size_t sentence_len;
    size_t alloc_size;
    
    if (sentence == NULL || adverbs == NULL || max_adverbs <= 0) {
        return 0;
    }
    
    sentence_len = safe_strlen(sentence, SENTENCE_BUFFER_SIZE - 1);
    
    if (sentence_len >= SENTENCE_BUFFER_SIZE - 1) {
        return 0;
    }
    
    alloc_size = sentence_len + 1;
    buffer = (char *)malloc(alloc_size);
    if (buffer == NULL) {
        return 0;
    }
    
    memcpy(buffer, sentence, sentence_len);
    buffer[sentence_len] = '\0';
    
    token = strtok_r(buffer, delimiters, &saveptr);
    while (token != NULL && count < max_adverbs) {
        size_t token_len = safe_strlen(token, MAX_WORD_LEN - 1);
        
        if (token_len > 0 && token_len < MAX_WORD_LEN) {
            char clean_word[MAX_WORD_LEN];
            size_t clean_len = 0;
            size_t i;
            
            for (i = 0; i < token_len && clean_len < MAX_WORD_LEN - 1; i++) {
                if (isalpha((unsigned char)token[i]) || token[i] == '-') {
                    clean_word[clean_len++] = token[i];
                }
            }
            clean_word[clean_len] = '\0';
            
            if (clean_len > 0 && clean_len < MAX_WORD_LEN) {
                char lower_word[MAX_WORD_LEN];
                size_t copy_len;
                
                copy_len = clean_len;
                if (copy_len >= MAX_WORD_LEN) {
                    copy_len = MAX_WORD_LEN - 1;
                }
                
                memcpy(lower_word, clean_word, copy_len);
                lower_word[copy_len] = '\0';
                to_lowercase(lower_word, MAX_WORD_LEN);
                
                if (is_adverb(lower_word)) {
                    size_t word_len;
                    
                    word_len = clean_len;
                    if (word_len >= MAX_WORD_LEN) {
                        word_len = MAX_WORD_LEN - 1;
                    }
                    
                    memcpy(adverbs[count].word, clean_word, word_len);
                    adverbs[count].word[word_len] = '\0';
                    adverbs[count].position = position;
                    count++;
                }
            }
        }
        
        position += (int)token_len;
        token = strtok_r(NULL, delimiters, &saveptr);
        if (token != NULL) {
            position++;
        }
    }
    
    free(buffer);
    return count;
}

int main(void) {
    const char *sentence = "The quick brown fox jumped extremely quickly over the lazy dog gracefully";
    AdverbInfo adverbs[MAX_WORDS];
    int count;
    int i;
    
    count = find_adverbs(sentence, adverbs, MAX_WORDS);
    
    printf("Adverbs found: %d\n", count);
    for (i = 0; i < count; i++) {
        printf("Adverb: '%s' at position %d\n", adverbs[i].word, adverbs[i].position);
    }
    
    return 0;
}