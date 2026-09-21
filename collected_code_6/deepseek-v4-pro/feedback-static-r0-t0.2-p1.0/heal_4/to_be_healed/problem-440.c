#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int position;
} AdverbInfo;

static int is_adverb(const char *word, size_t word_len) {
    if (word_len < 2) return 0;
    return (word[word_len - 2] == 'l' && word[word_len - 1] == 'y');
}

static size_t safe_str_copy(char *dest, const char *src, size_t dest_size) {
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

static size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) return 0;
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int find_adverbs(const char *sentence, AdverbInfo *adverbs, int max_adverbs) {
    if (sentence == NULL || adverbs == NULL || max_adverbs <= 0) {
        return -1;
    }

    if (max_adverbs > MAX_WORDS) {
        return -1;
    }

    size_t len = safe_strlen(sentence, SIZE_MAX / 2);
    
    if (len == SIZE_MAX / 2) {
        return -1;
    }

    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, sentence, len);
    buffer[len] = '\0';

    int count = 0;
    int pos = 0;
    const char *delimiters = " ,.!?;:\"()[]{}";
    char *saveptr = NULL;
    char *token = strtok_r(buffer, delimiters, &saveptr);
    
    while (token != NULL && count < max_adverbs) {
        size_t token_len = safe_strlen(token, MAX_WORD_LEN * 2);
        
        if (token_len >= MAX_WORD_LEN * 2) {
            break;
        }
        
        if (token_len > 0 && is_adverb(token, token_len)) {
            size_t copied = safe_str_copy(adverbs[count].word, token, MAX_WORD_LEN);
            if (copied < MAX_WORD_LEN) {
                adverbs[count].position = pos;
                count++;
            }
        }
        pos++;
        token = strtok_r(NULL, delimiters, &saveptr);
    }

    free(buffer);
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[512];
    AdverbInfo adverbs[MAX_WORDS];

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    size_t input_len = safe_strlen(sentence, sizeof(sentence));
    
    if (input_len > 0 && sentence[input_len - 1] == '\n') {
        sentence[input_len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'input_len' is assigned a value that is never used. [unreadVariable]
         */
        input_len--;
    } else if (input_len == sizeof(sentence) - 1) {
        sentence[sizeof(sentence) - 1] = '\0';
    }

    int result = find_adverbs(sentence, adverbs, MAX_WORDS);
    if (result < 0) {
        fprintf(stderr, "Error processing sentence\n");
        return 1;
    }

    if (result == 0) {
        printf("No adverbs found.\n");
    } else {
        printf("Adverbs found:\n");
        for (int i = 0; i < result; i++) {
            printf("Word: %s, Position: %d\n", adverbs[i].word, adverbs[i].position);
        }
    }

    return 0;
}