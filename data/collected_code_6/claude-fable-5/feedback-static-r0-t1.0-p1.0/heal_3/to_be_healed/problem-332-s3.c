#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define CHARSET_SIZE (UCHAR_MAX + 1)
#define INPUT_SIZE 256

int count_char_frequency(const char *str, size_t maxlen, size_t freq[], size_t freq_size)
{
    size_t i;

    if (str == NULL || freq == NULL || freq_size < CHARSET_SIZE) {
        return -1;
    }

    for (i = 0; i < freq_size; i++) {
        freq[i] = 0;
    }

    for (i = 0; i < maxlen && str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if ((size_t)c < freq_size) {
            freq[c]++;
        }
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    size_t freq[CHARSET_SIZE];
    size_t i;
    size_t len;

    printf("Enter a string: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error flushing output\n");
        return EXIT_FAILURE;
    }

    memset(input, 0, sizeof(input));

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        len--;
    }

    if (count_char_frequency(input, sizeof(input), freq, CHARSET_SIZE) != 0) {
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