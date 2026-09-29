#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_word_present(const char *sentence, size_t sentence_len, const char *word, size_t word_len) {
    if (sentence == NULL || word == NULL) {
        return false;
    }
    
    if (word_len == 0) {
        return false;
    }
    
    if (sentence_len < word_len) {
        return false;
    }
    
    for (size_t i = 0; i <= sentence_len - word_len; i++) {
        if (memcmp(sentence + i, word, word_len) == 0) {
            bool start_ok = (i == 0) || !isalnum((unsigned char)sentence[i - 1]);
            bool end_ok = (i + word_len >= sentence_len) || !isalnum((unsigned char)sentence[i + word_len]);
            
            if (start_ok && end_ok) {
                return true;
            }
        }
    }
    
    return false;
}

int main(void) {
    char *sentence = NULL;
    char *word = NULL;
    size_t sentence_size = 0;
    size_t word_size = 0;
    ssize_t sentence_len;
    ssize_t word_len;
    int result = 1;
    
    sentence_len = getline(&sentence, &sentence_size, stdin);
    if (sentence_len == -1) {
        goto cleanup;
    }
    
    if (sentence_len > 0 && sentence[sentence_len - 1] == '\n') {
        sentence[sentence_len - 1] = '\0';
        sentence_len--;
    }
    
    word_len = getline(&word, &word_size, stdin);
    if (word_len == -1) {
        goto cleanup;
    }
    
    if (word_len > 0 && word[word_len - 1] == '\n') {
        word[word_len - 1] = '\0';
        word_len--;
    }
    
    if (is_word_present(sentence, (size_t)sentence_len, word, (size_t)word_len)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    result = 0;
    
cleanup:
    free(sentence);
    free(word);
    return result;
}