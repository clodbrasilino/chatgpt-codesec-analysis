#include <stdio.h>
#include <string.h>

int is_even_length(const char *word, size_t max_len) {
    if (word == NULL) {
        return -1;
    }
    size_t len = strnlen(word, max_len);
    if (len == max_len && word[len] != '\0') {
        return -1;
    }
    return (len % 2 == 0) ? 1 : 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[100];
    
    printf("Enter a word: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strnlen(word, sizeof(word));
    if (len == sizeof(word)) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    word[strcspn(word, "\n")] = '\0';
    
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