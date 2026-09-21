#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LEN 256

bool is_length_even(const char *word) {
    if (word == NULL) {
        return false;
    }
    
    size_t length = strnlen(word, MAX_WORD_LEN);
    return (length % 2 == 0);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN] = {0};

    if (fgets(word, sizeof(word), stdin) != NULL) {
        word[strcspn(word, " \t\r\n")] = '\0';
        
        if (word[0] != '\0') {
            if (is_length_even(word)) {
                printf("Even\n");
            } else {
                printf("Odd\n");
            }
        }
    }

    return 0;
}