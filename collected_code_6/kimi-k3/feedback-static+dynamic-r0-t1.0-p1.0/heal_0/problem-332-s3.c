#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_CHARS 256

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