#include <stdio.h>
#include <string.h>

int find_word(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);
    if (word_len == 0) {
        return 0;
    }
    
    const char *ptr = sentence;
    while ((ptr = strstr(ptr, word)) != NULL) {
        int left_boundary = (ptr == sentence) || (*(ptr - 1) == ' ') || (*(ptr - 1) == '\t') || (*(ptr - 1) == '\n') || (*(ptr - 1) == '\r');
        
        const char *end_ptr = ptr + word_len;
        int right_boundary = (*end_ptr == '\0') || (*end_ptr == ' ') || (*end_ptr == '\t') || (*end_ptr == '\n') || (*end_ptr == '\r') || (*end_ptr == '.') || (*end_ptr == ',') || (*end_ptr == '!') || (*end_ptr == '?');
        
        if (left_boundary && right_boundary) {
            return 1;
        }
        
        ptr++;
    }
    
    return 0;
}

int main(void) {
    const char *sentence = "The quick brown fox jumps over the lazy dog";
    const char *word_to_find = "brown";
    const char *missing_word = "cat";
    
    if (find_word(sentence, word_to_find)) {
        printf("Word '%s' found.\n", word_to_find);
    } else {
        printf("Word '%s' not found.\n", word_to_find);
    }
    
    if (find_word(sentence, missing_word)) {
        printf("Word '%s' found.\n", missing_word);
    } else {
        printf("Word '%s' not found.\n", missing_word);
    }
    
    return 0;
}