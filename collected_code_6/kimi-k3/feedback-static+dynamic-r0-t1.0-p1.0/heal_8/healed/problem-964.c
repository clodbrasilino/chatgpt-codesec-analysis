#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_even_length(const char *word, size_t max_len) {
    if (word == NULL || max_len == 0) {
        return false;
    }
    size_t length = strnlen(word, max_len);
    return (length % 2 == 0);
}

int main(void) {
    char buffer[256];
    
    printf("Enter a word: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    if (is_even_length(buffer, sizeof(buffer))) {
        printf("The length is even\n");
    } else {
        printf("The length is odd\n");
    }
    
    return EXIT_SUCCESS;
}