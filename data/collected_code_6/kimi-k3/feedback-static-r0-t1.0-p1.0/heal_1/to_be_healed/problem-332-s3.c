#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_CHARS 256

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
void count_char_frequency(const char *str, int freq[NUM_CHARS]) {
    size_t i;
    
    if (str == NULL || freq == NULL) {
        return;
    }
    
    for (i = 0; i < NUM_CHARS; i++) {
        freq[i] = 0;
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        freq[(unsigned char)str[i]]++;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    int frequency[NUM_CHARS];
    int i;
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    count_char_frequency(buffer, frequency);
    
    printf("Character frequencies:\n");
    for (i = 0; i < NUM_CHARS; i++) {
        if (frequency[i] > 0) {
            if (i >= 32 && i <= 126) {
                printf("'%c': %d\n", i, frequency[i]);
            } else {
                printf("ASCII %d: %d\n", i, frequency[i]);
            }
        }
    }
    
    return EXIT_SUCCESS;
}