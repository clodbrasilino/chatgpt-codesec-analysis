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
    char *safe_word = malloc(arg_len + 1);
    if (safe_word == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(safe_word, argv[1], arg_len + 1);
    
    if (is_odd_length(safe_word, max_len)) {
        printf("odd\n");
    } else {
        printf("even\n");
    }
    
    free(safe_word);
    return 0;
}