#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 256
#define MAX_WORD_LEN 64
#define MAX_ADVERB_LEN 32
#define BUFFER_SIZE 1024

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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

static int ends_with(const char *str, const char *suffix) {
    size_t str_len;
    size_t suffix_len;
    
    if (str == NULL || suffix == NULL) {
        return 0;
    }
    
    str_len = safe_strlen(str, MAX_WORD_LEN);
    suffix_len = safe_strlen(suffix, MAX_ADVERB_LEN);
    
    if (str_len < suffix_len || suffix_len == 0) {
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
    
    len = safe_strlen(word, MAX_WORD_LEN);
    
    if (len < 2 || len >= MAX_ADVERB_LEN) {
        return 0;
    }
    
    if (isupper((unsigned char)word[0])) {
        return 0;
    }
    
    for (i = 0; adverb_suffixes[i] != NULL; i++) {
        if (ends_with(word, adverb_suffixes[i])) {
            if (strncmp(word, "family", MAX_WORD_LEN) == 0 || 
                strncmp(word, "rely", MAX_WORD_LEN) == 0 ||
                strncmp(word, "apply", MAX_WORD_LEN) == 0 || 
                strncmp(word, "supply", MAX_WORD_LEN) == 0) {
                continue;
            }
            return 1;
        }
    }
    
    return 0;
}

static void to_lowercase(char *str, size_t max_len) {
    size_t i;
    if (str == NULL) {
        return;
    }
    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

static size_t safe_strncpy(char *dest, const char *src, size_t dest_size) {
    size_t i;
    size_t src_len;
    
    if (dest == NULL || src == NULL || dest_size == 0) {
        if (dest != NULL && dest_size > 0) {
            dest[0] = '\0';
        }
        return 0;
    }
    
    src_len = safe_strlen(src, dest_size);
    
    if (src_len >= dest_size) {
        src_len = dest_size - 1;
    }
    
    for (i = 0; i < src_len; i++) {
        dest[i] = src[i];
    }
    dest[src_len] = '\0';
    
    return src_len;
}

static int find_adverbs(const char *sentence, AdverbInfo *adverbs, int max_adverbs) {
    char *buffer = NULL;
    char *token;
    const char *delimiters = " \t\n\r.,;:!?\"'()[]{}";
    int count = 0;
    int position = 0;
    char *saveptr;
    size_t sentence_len;
    size_t buffer_size;
    
    if (sentence == NULL || adverbs == NULL || max_adverbs <= 0) {
        return 0;
    }
    
    sentence_len = safe_strlen(sentence, BUFFER_SIZE - 1);
    
    if (sentence_len == 0 || sentence_len >= BUFFER_SIZE - 1) {
        return 0;
    }
    
    buffer_size = sentence_len + 1;
    
    if (buffer_size > BUFFER_SIZE) {
        return 0;
    }
    
    buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        return 0;
    }
    
    if (sentence_len >= buffer_size) {
        free(buffer);
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, sentence, sentence_len);
    buffer[sentence_len] = '\0';
    
    token = strtok_r(buffer, delimiters, &saveptr);
    while (token != NULL && count < max_adverbs) {
        size_t token_len = safe_strlen(token, MAX_WORD_LEN);
        if (token_len > 0 && token_len < MAX_WORD_LEN) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char clean_word[MAX_WORD_LEN];
            size_t clean_len = 0;
            size_t i;
            
            for (i = 0; i < token_len && i < MAX_WORD_LEN - 1; i++) {
                if (isalpha((unsigned char)token[i]) || token[i] == '-') {
                    if (clean_len < MAX_WORD_LEN - 1) {
                        clean_word[clean_len++] = token[i];
                    }
                }
            }
            clean_word[clean_len] = '\0';
            
            if (clean_len > 0 && clean_len < MAX_WORD_LEN) {
                /* Possible weaknesses found:
                 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
                 */
                char lower_word[MAX_WORD_LEN];
                size_t lower_len = safe_strncpy(lower_word, clean_word, sizeof(lower_word));
                if (lower_len > 0 && lower_len < MAX_WORD_LEN) {
                    to_lowercase(lower_word, sizeof(lower_word));
                    
                    if (is_adverb(lower_word)) {
                        size_t copied = safe_strncpy(adverbs[count].word, clean_word, MAX_WORD_LEN);
                        if (copied > 0) {
                            adverbs[count].position = position;
                            count++;
                        }
                    }
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