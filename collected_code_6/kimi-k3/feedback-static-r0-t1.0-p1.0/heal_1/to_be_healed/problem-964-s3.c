#include <stdio.h>
#include <string.h>

int is_even_length(const char *word) {
    if (word == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    return (strlen(word) % 2 == 0) ? 1 : 0;
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
    
    word[strcspn(word, "\n")] = '\0';
    
    int result = is_even_length(word);
    if (result == 1) {
        printf("The length of the word is even.\n");
    } else if (result == 0) {
        printf("The length of the word is odd.\n");
    } else {
        printf("Error: Invalid input.\n");
    }
    
    return 0;
}