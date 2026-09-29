#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate_min_length(const char *str, size_t max_len) {
    size_t len = strnlen(str, max_len);
    if (len == 0) {
        return 0;
    }

    size_t count[256] = {0};
    for (size_t i = 0; i < len; i++) {
        unsigned char c = str[i];
        count[c]++;
    }

    size_t min_count = len;
    for (int i = 0; i < 256; i++) {
        if (count[i] > 0 && count[i] < min_count) {
            min_count = count[i];
        }
    }

    if (min_count > len) {
        return (int)len;
    }

    return (int)(len - min_count);
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    size_t input_len = strnlen(argv[1], 4097);
    if (input_len > 4096) {
        fprintf(stderr, "Error: Input string exceeds maximum allowed length\n");
        return 1;
    }

    int result = calculate_min_length(argv[1], 4096);
    printf("%d\n", result);

    return 0;
}