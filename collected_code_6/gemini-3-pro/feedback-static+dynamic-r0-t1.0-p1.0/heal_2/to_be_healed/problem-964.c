#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_length_even(const char *word, size_t max_len) {
    if (word == NULL) {
        return false;
    }
    
    size_t length = 0;
    while (length < max_len && word[length] != '\0' && word[length] != '\n') {
        length++;
    }
    
    return (length % 2 == 0);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[256];

    if (fgets(word, sizeof(word), stdin) != NULL) {
        if (is_length_even(word, sizeof(word))) {
            printf("Even\n");
        } else {
            printf("Odd\n");
        }
    }

    return 0;
}