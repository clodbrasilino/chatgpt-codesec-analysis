#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_SIZE 256

void count_character_frequency(const char *str, int *freq, size_t freq_size) {
    if (str == NULL || freq == NULL || freq_size < ASCII_SIZE) {
        return;
    }

    memset(freq, 0, ASCII_SIZE * sizeof(int));

    for (size_t i = 0; str[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)str[i];
        freq[ch]++;
    }
}

int main(void) {
    char *input = NULL;
    size_t buffer_size = 1024;
    size_t input_length;
    int frequency[ASCII_SIZE] = {0};

    input = (char *)malloc(buffer_size * sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");
    if (fgets(input, (int)buffer_size, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    input_length = strlen(input);
    if (input_length > 0 && input[input_length - 1] != '\n' && input_length == buffer_size - 1) {
        fprintf(stderr, "Input exceeds maximum allowed length\n");
        free(input);
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    count_character_frequency(input, frequency, ASCII_SIZE);

    printf("Character frequencies:\n");
    for (int i = 0; i < ASCII_SIZE; i++) {
        if (frequency[i] > 0) {
            printf("'%c' (%d): %d\n", i, i, frequency[i]);
        }
    }

    free(input);
    return EXIT_SUCCESS;
}