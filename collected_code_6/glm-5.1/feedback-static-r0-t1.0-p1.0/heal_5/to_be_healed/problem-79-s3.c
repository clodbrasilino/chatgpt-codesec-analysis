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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <word>\n", argv[0]);
        return 1;
    }
    
    size_t arg_len = strnlen(argv[1], 1024);
    char *safe_word = malloc(arg_len + 1);
    if (safe_word == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(safe_word, argv[1], arg_len);
    safe_word[arg_len] = '\0';
    
    if (is_odd_length(safe_word, 1024)) {
        printf("odd\n");
    } else {
        printf("even\n");
    }
    
    free(safe_word);
    return 0;
}