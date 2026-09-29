#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 2 failed: expected False, got <no output>
  */

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
    }
    
    word_len = getline(&word, &word_size, stdin);
    if (word_len == -1) {
        goto cleanup;
    }
    
    if (word_len > 0 && word[word_len - 1] == '\n') {
        word[word_len - 1] = '\0';
    }
    
    if (is_word_present(sentence, word)) {
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