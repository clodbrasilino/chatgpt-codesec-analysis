#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORD_LEN 256

bool word_contains_z(const char *word)
{
    if (word == NULL) {
        return false;
    }
    
    size_t i;
    size_t len = strlen(word);
    
    if (len == 0 || len >= MAX_WORD_LEN) {
        return false;
    }
    
    for (i = 0; i < len; i++) {
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
    
    size_t len = strlen(word);
    if (len > 0 && word[len - 1] == '\n') {
        word[len - 1] = '\0';
    }
    
    if (word_contains_z(word)) {
        printf("The word contains 'z'.\n");
    } else {
        printf("The word does not contain 'z'.\n");
    }
    
    return EXIT_SUCCESS;
}