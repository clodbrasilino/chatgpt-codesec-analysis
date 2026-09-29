#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHARSET_SIZE 256

int count_char_frequency(const char *str, size_t freq[CHARSET_SIZE])
{
    size_t i;
    size_t len;

    if (str == NULL || freq == NULL) {
        return -1;
    }

    memset(freq, 0, CHARSET_SIZE * sizeof(size_t));

    len = strlen(str);
    for (i = 0; i < len; i++) {
        freq[(unsigned char)str[i]]++;
    }

    return 0;
}

int main(void)
{
    char buffer[1024];
    size_t freq[CHARSET_SIZE];
    size_t i;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    if (count_char_frequency(buffer, freq) != 0) {
        fprintf(stderr, "Error counting character frequency\n");
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