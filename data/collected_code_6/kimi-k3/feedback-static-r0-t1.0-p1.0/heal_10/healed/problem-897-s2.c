#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>

#define SENTENCE_SIZE 256
#define WORD_SIZE 64

bool is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return false;
    }
    
    size_t word_len = strnlen(word, WORD_SIZE);
    
    if (word_len == 0 || word_len >= WORD_SIZE) {
        return false;
    }
    
    size_t sentence_len = strnlen(sentence, SENTENCE_SIZE);
    const char *pos = sentence;
    const char *end = sentence + sentence_len;
    
    while (pos < end && (size_t)(end - pos) >= word_len) {
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

static void flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static bool read_input(char *buffer, size_t buffer_size) {
    if (buffer == NULL || buffer_size == 0) {
        return false;
    }
    
    if (fgets(buffer, buffer_size, stdin) == NULL) {
        return false;
    }
    
    size_t len = strnlen(buffer, buffer_size);
    
    if (len == 0) {
        return false;
    }
    
    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == buffer_size - 1) {
        flush_input();
    }
    
    return true;
}

int main(void) {
    char sentence[SENTENCE_SIZE];
    char word[WORD_SIZE];
    
    printf("Enter a sentence: ");
    if (!read_input(sentence, sizeof(sentence))) {
        fprintf(stderr, "Error reading sentence\n");
        return 1;
    }
    
    printf("Enter a word to search: ");
    if (!read_input(word, sizeof(word))) {
        fprintf(stderr, "Error reading word\n");
        return 1;
    }
    
    if (is_word_present(sentence, word)) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }
    
    return 0;
}