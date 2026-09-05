#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

bool can_rearrange(const char *str) {
    size_t len = strlen(str);
    if (len == 0) {
        return true;
    }

    size_t freq[UCHAR_MAX + 1] = {0};
    size_t max_freq = 0;

    for (size_t i = 0; i < len; ++i) {
        unsigned char c = str[i];
        freq[c]++;
        if (freq[c] > max_freq) {
            max_freq = freq[c];
        }
    }

    return max_freq <= (len + 1) / 2;
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (can_rearrange(argv[1])) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return EXIT_SUCCESS;
}