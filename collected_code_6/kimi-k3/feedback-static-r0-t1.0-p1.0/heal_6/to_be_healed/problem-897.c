#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return false;
    }

    size_t word_len = strnlen(word, 64);
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
        if (ch == EOF) {
            break;
        }
    }
}

static bool read_input(char *buffer, size_t buffer_size, const char *prompt) {
    if (buffer == NULL || buffer_size == 0 || prompt == NULL) {
        return false;
    }
    
    if (buffer_size > 256) {
        return false;
    }
    
    printf("%s", prompt);
    
    if (fgets(buffer, buffer_size, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return false;
    }
    
    size_t len = strnlen(buffer, buffer_size);
    
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[64];
    
    if (!read_input(sentence, sizeof(sentence), "Enter a sentence: ")) {
        return 1;
    }
    
    if (!read_input(word, sizeof(word), "Enter a word to search: ")) {
        return 1;
    }
    
    if (is_word_present(sentence, word)) {
        printf("Word found in the sentence\n");
    } else {
        printf("Word not found in the sentence\n");
    }
    
    return 0;
}