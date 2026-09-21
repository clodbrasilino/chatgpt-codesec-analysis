#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 256

void reverse_substring(char *start, char *end) {
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void reverse_words(char *str) {
    if (str == NULL || *str == '\0') {
        return;
    }
    
    char *word_start = NULL;
    char *current = str;
    
    while (*current != '\0') {
        if (word_start == NULL && !isspace((unsigned char)*current)) {
            word_start = current;
        }
        if (word_start != NULL && (isspace((unsigned char)*(current + 1)) || *(current + 1) == '\0')) {
            reverse_substring(word_start, current);
            word_start = NULL;
        }
        current++;
    }
    
    reverse_substring(str, current - 1);
}

int main(void) {
    char buffer[BUFFER_SIZE];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (!feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    reverse_words(buffer);
    
    if (printf("%s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}