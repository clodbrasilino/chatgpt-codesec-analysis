#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 256
#define MAX_WORD_LEN 64
#define MAX_ADVERB_LEN 32

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
    
    if (str_len < suffix_len) {
        return 0;
    }
    
    return strcmp(str + str_len - suffix_len, suffix) == 0;
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
        if (ends_with(word, adverb_suffixes[i])) {
            if (strcmp(word, "family") == 0 || strcmp(word, "rely") == 0 ||
                strcmp(word, "apply") == 0 || strcmp(word, "supply") == 0) {
                continue;
            }
            return 1;
        }
    }
    
    return 0;
}

static void to_lowercase(char *str) {
    int i;
    if (str == NULL) {
        return;
    }
    /* Possible weaknesses found:
     *  Array index 'i' is used before limits check. [arrayIndexThenCheck]
     */
    for (i = 0; str[i] != '\0' && i < MAX_WORD_LEN - 1; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

static size_t safe_strncpy(char *dest, const char *src, size_t dest_size) {
    size_t i;
    
    if (dest == NULL || src == NULL || dest_size == 0) {
        if (dest != NULL && dest_size > 0) {
            dest[0] = '\0';
        }
        return 0;
    }
    
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    
    return i;
}

static int find_adverbs(const char *sentence, AdverbInfo *adverbs, int max_adverbs) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    char *token;
    const char *delimiters = " \t\n\r.,;:!?\"'()[]{}";
    int count = 0;
    int position = 0;
    char *saveptr;
    size_t sentence_len;
    
    if (sentence == NULL || adverbs == NULL || max_adverbs <= 0) {
        return 0;
    }
    
    sentence_len = safe_strlen(sentence, 1023);
    if (sentence_len >= sizeof(buffer)) {
        sentence_len = sizeof(buffer) - 1;
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
                    clean_word[clean_len++] = token[i];
                }
            }
            clean_word[clean_len] = '\0';
            
            if (clean_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
                 */
                char lower_word[MAX_WORD_LEN];
                safe_strncpy(lower_word, clean_word, sizeof(lower_word));
                to_lowercase(lower_word);
                
                if (is_adverb(lower_word)) {
                    safe_strncpy(adverbs[count].word, clean_word, MAX_WORD_LEN);
                    adverbs[count].position = position;
                    count++;
                }
            }
        }
        
        position += (int)safe_strlen(token, MAX_WORD_LEN);
        token = strtok_r(NULL, delimiters, &saveptr);
        if (token != NULL) {
            position++;
        }
    }
    
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