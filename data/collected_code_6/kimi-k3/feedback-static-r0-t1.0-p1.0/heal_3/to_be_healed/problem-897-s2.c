#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>

bool is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return false;
    }
    
    size_t word_len = 0;
    while (word_len < 64 && word[word_len] != '\0') {
        word_len++;
    }
    
    if (word_len == 0 || word_len >= 64) {
        return false;
    }
    
    const char *pos = sentence;
    const char *end = sentence;
    size_t remaining = 256;
    
    while (remaining > 0 && *end != '\0') {
        end++;
        remaining--;
    }
    
    while (pos < end && (end - pos) >= (ptrdiff_t)word_len) {
        const char *found = NULL;
        for (const char *p = pos; p <= end - word_len; p++) {
            if (strncmp(p, word, word_len) == 0) {
                found = p;
                break;
            }
        }
        
        if (found == NULL) {
            break;
        }
        
        pos = found;
        bool start_ok = (pos == sentence) || !isalnum((unsigned char)pos[-1]);
        bool end_ok = (pos + word_len >= end) || !isalnum((unsigned char)pos[word_len]);
        
        if (start_ok && end_ok) {
            return true;
        }
        pos++;
    }
    
    return false;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[64];
    
    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading sentence\n");
        return 1;
    }
    
    size_t len = 0;
    while (len < sizeof(sentence) && sentence[len] != '\0') {
        len++;
    }
    
    if (len > 0 && len <= sizeof(sentence) && sentence[len - 1] == '\n') {
        sentence[len - 1] = '\0';
    } else if (len == sizeof(sentence)) {
        sentence[sizeof(sentence) - 1] = '\0';
    }
    
    printf("Enter a word to search: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        fprintf(stderr, "Error reading word\n");
        return 1;
    }
    
    len = 0;
    while (len < sizeof(word) && word[len] != '\0') {
        len++;
    }
    
    if (len > 0 && len <= sizeof(word) && word[len - 1] == '\n') {
        word[len - 1] = '\0';
    } else if (len == sizeof(word)) {
        word[sizeof(word) - 1] = '\0';
    }
    
    if (is_word_present(sentence, word)) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }
    
    return 0;
}