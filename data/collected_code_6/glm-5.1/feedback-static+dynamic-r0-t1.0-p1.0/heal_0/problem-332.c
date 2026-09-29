#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void count_char_frequency(const char *str, size_t *freq) {
    if (str == NULL || freq == NULL) {
        return;
    }

    for (size_t i = 0; i < (size_t)UCHAR_MAX; ++i) {
        freq[i] = 0;
    }

    for (size_t i = 0; str[i] != '\0'; ++i) {
        unsigned char c = (unsigned char)str[i];
        freq[c]++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t *freq = malloc((size_t)UCHAR_MAX * sizeof(size_t));
    if (freq == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    count_char_frequency(argv[1], freq);

    for (size_t i = 0; i < (size_t)UCHAR_MAX; ++i) {
        if (freq[i] > 0) {
            if (isprint((unsigned char)i)) {
                printf("'%c': %zu\n", (char)i, freq[i]);
            } else {
                printf("0x%02X: %zu\n", (unsigned int)i, freq[i]);
            }
        }
    }

    free(freq);
    freq = NULL;

    return EXIT_SUCCESS;
}