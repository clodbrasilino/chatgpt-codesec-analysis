#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

#define NUM_CHARS 256
#define BUFFER_SIZE 1024

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
void count_char_frequency(const char *str, size_t freq[NUM_CHARS]) {
    size_t i;
    
    if (str == NULL || freq == NULL) {
        return;
    }
    
    for (i = 0; i < NUM_CHARS; i++) {
        freq[i] = 0;
    }
    
    /* Possible weaknesses found:
     *  Array index 'i' is used before limits check. [arrayIndexThenCheck]
     */
    for (i = 0; str[i] != '\0' && i < BUFFER_SIZE - 1; i++) {
        unsigned char c = (unsigned char)str[i];
        if (freq[c] < SIZE_MAX) {
            freq[c]++;
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    size_t frequency[NUM_CHARS];
    int i;
    
    printf("Enter a string: ");
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    count_char_frequency(buffer, frequency);
    
    printf("Character frequencies:\n");
    for (i = 0; i < NUM_CHARS; i++) {
        if (frequency[i] > 0) {
            if (i >= 32 && i <= 126) {
                printf("'%c': %zu\n", i, frequency[i]);
            } else {
                printf("ASCII %d: %zu\n", i, frequency[i]);
            }
        }
    }
    
    return EXIT_SUCCESS;
}