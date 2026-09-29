#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int is_even_length(const char *word, size_t max_len) {
    if (word == NULL || max_len == 0) {
        return -1;
    }
    size_t len = strnlen(word, max_len);
    if (len == max_len) {
        return -1;
    }
    return (len % 2 == 0) ? 1 : 0;
}

int main(void) {
    char word[100];
    
    printf("Enter a word: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strcspn(word, "\n");
    if (len == 0 && !feof(stdin)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Error: Input too long.\n");
        return 1;
    }
    word[len] = '\0';
    
    int result = is_even_length(word, sizeof(word));
    if (result == 1) {
        printf("The length of the word is even.\n");
    } else if (result == 0) {
        printf("The length of the word is odd.\n");
    } else {
        printf("Error: Invalid input.\n");
    }
    
    return 0;
}