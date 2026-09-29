#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

#define NUM_CHARS 256
#define BUFFER_SIZE 1024

void count_char_frequency(const char *str, size_t freq[NUM_CHARS]) {
    size_t i;
    
    if (str == NULL || freq == NULL) {
        return;
    }
    
    for (i = 0; i < NUM_CHARS; i++) {
        freq[i] = 0;
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (freq[c] < SIZE_MAX) {
            freq[c]++;
        }
    }
}

int main(void) {
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