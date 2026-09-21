#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_odd_length(const char *word, size_t max_len) {
    if (word == NULL) {
        return false;
    }
    size_t len = strnlen(word, max_len);
    return len % 2 != 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <word>\n", argv[0]);
        return 1;
    }
    
    size_t max_len = 1024;
    size_t arg_len = strnlen(argv[1], max_len);
    
    if (arg_len == max_len) {
        fprintf(stderr, "Argument exceeds maximum allowed length\n");
        return 1;
    }
    
    char *safe_word = malloc(arg_len + 1);
    if (safe_word == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    memcpy(safe_word, argv[1], arg_len + 1);
    safe_word[arg_len] = '\0';
    
    if (is_odd_length(safe_word, max_len)) {
        printf("odd\n");
    } else {
        printf("even\n");
    }
    
    free(safe_word);
    return 0;
}