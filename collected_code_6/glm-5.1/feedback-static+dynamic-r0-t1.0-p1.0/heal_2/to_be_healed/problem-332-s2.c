#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define ASCII_SIZE 256

void count_char_frequency(const char *str, unsigned long *freq) {
    if (str == NULL || freq == NULL) {
        return;
    }

    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        unsigned char c = str[i];
        freq[c]++;
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned long *freq = calloc(ASCII_SIZE, sizeof(unsigned long));
    if (freq == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    count_char_frequency(argv[1], freq);

    for (int i = 0; i < ASCII_SIZE; i++) {
        if (freq[i] > 0) {
            if (isprint(i)) {
                printf("'%c': %lu\n", i, freq[i]);
            } else {
                printf("0x%02x: %lu\n", i, freq[i]);
            }
        }
    }

    free(freq);
    freq = NULL;

    return EXIT_SUCCESS;
}