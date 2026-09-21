#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_SIZE 256
#define INPUT_BUFFER_SIZE 1024

void count_character_frequency(const char *str, int *freq, size_t freq_size) {
    if (str == NULL || freq == NULL || freq_size < ASCII_SIZE) {
        return;
    }

    memset(freq, 0, ASCII_SIZE * sizeof(int));

    for (size_t i = 0; i < INPUT_BUFFER_SIZE - 1 && str[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)str[i];
        freq[ch]++;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    int frequency[ASCII_SIZE] = {0};

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    size_t length = 0;
    while (length < INPUT_BUFFER_SIZE && input[length] != '\0') {
        length++;
    }

    if (length >= INPUT_BUFFER_SIZE) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    count_character_frequency(input, frequency, ASCII_SIZE);

    printf("Character frequencies:\n");
    for (int i = 0; i < ASCII_SIZE; i++) {
        if (frequency[i] > 0) {
            printf("'%c' (%d): %d\n", (char)i, i, frequency[i]);
        }
    }

    return EXIT_SUCCESS;
}