#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_SIZE 256

int *count_char_frequency(const char *str, size_t max_len) {
    int *frequency = (int *)calloc(ASCII_SIZE, sizeof(int));
    if (frequency == NULL) {
        return NULL;
    }

    if (str != NULL) {
        size_t i = 0;
        while (i < max_len && str[i] != '\0') {
            unsigned char c = (unsigned char)str[i];
            frequency[c]++;
            i++;
        }
    }

    return frequency;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    size_t max_len = strnlen(input, 1024) + 1;
    
    int *frequency = count_char_frequency(input, max_len);
    
    if (frequency == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < ASCII_SIZE; i++) {
        if (frequency[i] > 0) {
            printf("%c: %d\n", (char)i, frequency[i]);
        }
    }

    free(frequency);
    frequency = NULL;

    return EXIT_SUCCESS;
}