#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define CHARSET_SIZE (UCHAR_MAX + 1)
#define INPUT_SIZE 256

int count_char_frequency(const char *str, size_t str_size, size_t freq[CHARSET_SIZE])
{
    size_t i;

    if (str == NULL || freq == NULL || str_size == 0) {
        return -1;
    }

    memset(freq, 0, CHARSET_SIZE * sizeof(size_t));

    for (i = 0; i < str_size && str[i] != '\0'; i++) {
        freq[(unsigned char)str[i]]++;
    }

    if (i == str_size) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[INPUT_SIZE];
    size_t freq[CHARSET_SIZE];
    size_t i;
    size_t len;

    printf("Enter a string: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len >= sizeof(input)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (count_char_frequency(input, sizeof(input), freq) != 0) {
        fprintf(stderr, "Failed to count character frequency\n");
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

    return EXIT_SUCCESS;
}