#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_even_length(const char *word) {
    if (word == NULL) {
        return false;
    }
    size_t length = strlen(word);
    return (length % 2 == 0);
}

int main(void) {
    char buffer[256];
    
    printf("Enter a word: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    if (is_even_length(buffer)) {
        printf("The length is even\n");
    } else {
        printf("The length is odd\n");
    }
    
    return EXIT_SUCCESS;
}