#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);
    if (word_len == 0) {
        return false;
    }

    const char *current = sentence;
    while ((current = strstr(current, word)) != NULL) {
        bool start_ok = (current == sentence) || !isalnum((unsigned char)current[-1]);
        bool end_ok = !isalnum((unsigned char)current[word_len]);
        
        if (start_ok && end_ok) {
            return true;
        }
        current++;
    }
    
    return false;
}

static void flush_input(void) {
    int ch;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

static bool read_input(char *buffer, size_t buffer_size, const char *prompt) {
    if (buffer == NULL || buffer_size == 0 || prompt == NULL) {
        return false;
    }
    
    printf("%s", prompt);
    
    if (fgets(buffer, buffer_size, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    
    if (len == 0) {
        fprintf(stderr, "Empty input\n");
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
    char *sentence = NULL;
    char *word = NULL;
    size_t sentence_size = 256;
    size_t word_size = 64;
    
    sentence = (char *)malloc(sentence_size);
    if (sentence == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    word = (char *)malloc(word_size);
    if (word == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(sentence);
        return 1;
    }
    
    if (!read_input(sentence, sentence_size, "Enter a sentence: ")) {
        free(sentence);
        free(word);
        return 1;
    }
    
    if (!read_input(word, word_size, "Enter a word to search: ")) {
        free(sentence);
        free(word);
        return 1;
    }
    
    if (is_word_present(sentence, word)) {
        printf("Word found in the sentence\n");
    } else {
        printf("Word not found in the sentence\n");
    }
    
    free(sentence);
    free(word);
    
    return 0;
}