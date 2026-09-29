#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define CHARSET_SIZE (UCHAR_MAX + 1)
#define INPUT_SIZE 256

int count_char_frequency(const char *str, size_t str_size, size_t freq[], size_t freq_size)
{
    size_t i;

    if (str == NULL || freq == NULL || str_size == 0 || freq_size < CHARSET_SIZE) {
        return -1;
    }

    memset(freq, 0, freq_size * sizeof(size_t));

    for (i = 0; i < str_size && str[i] != '\0'; i++) {
        unsigned char idx = (unsigned char)str[i];
        if ((size_t)idx < freq_size) {
            if (freq[idx] < SIZE_MAX) {
                freq[idx]++;
            }
        }
    }

    if (i == str_size) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char *input;
    size_t *freq;
    size_t i;
    size_t len;

    input = calloc(INPUT_SIZE, sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    freq = calloc(CHARSET_SIZE, sizeof(size_t));
    if (freq == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");
    if (fflush(stdout) != 0) {
        free(input);
        free(freq);
        return EXIT_FAILURE;
    }

    if (fgets(input, INPUT_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        free(freq);
        return EXIT_FAILURE;
    }

    input[INPUT_SIZE - 1] = '\0';

    len = strnlen(input, INPUT_SIZE);
    if (len >= INPUT_SIZE) {
        fprintf(stderr, "Input too long\n");
        free(input);
        free(freq);
        return EXIT_FAILURE;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (count_char_frequency(input, len + 1, freq, CHARSET_SIZE) != 0) {
        fprintf(stderr, "Failed to count character frequency\n");
        free(input);
        free(freq);
        return EXIT_FAILURE;
    }

    for (i = 0; i < CHARSET_SIZE; i++) {
        if (freq[i] > 0) {
            if (i >= 32 && i < 127) {
                printf("'%c' : %zu\n", (int)i, freq[i]);
            } else {
                printf("0x%02zX : %zu\n", i, freq[i]);
            }
        }
    }

    free(input);
    free(freq);

    return EXIT_SUCCESS;
}