#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORD_LEN 256

bool word_contains_z(const char *word, size_t max_len)
{
    if (word == NULL) {
        return false;
    }
    
    size_t len = 0;
    bool null_found = false;
    
    for (size_t i = 0; i < max_len; i++) {
        if (word[i] == '\0') {
            null_found = true;
            len = i;
            break;
        }
    }
    
    if (!null_found || len == 0 || len >= MAX_WORD_LEN) {
        return false;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (word[i] == 'z' || word[i] == 'Z') {
            return true;
        }
    }
    
    return false;
}

int main(void)
{
    char word[MAX_WORD_LEN];
    
    printf("Enter a word: ");
    
    if (fgets(word, sizeof(word), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = 0;
    bool null_found = false;
    
    for (size_t i = 0; i < sizeof(word); i++) {
        if (word[i] == '\0') {
            null_found = true;
            len = i;
            break;
        }
    }
    
    if (!null_found) {
        word[sizeof(word) - 1] = '\0';
        len = sizeof(word) - 1;
    }
    
    if (len > 0 && word[len - 1] == '\n') {
        word[len - 1] = '\0';
    }
    
    if (word_contains_z(word, sizeof(word))) {
        printf("The word contains 'z'.\n");
    } else {
        printf("The word does not contain 'z'.\n");
    }
    
    return EXIT_SUCCESS;
}