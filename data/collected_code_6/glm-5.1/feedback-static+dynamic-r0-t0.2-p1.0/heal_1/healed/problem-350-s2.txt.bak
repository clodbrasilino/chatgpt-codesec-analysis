#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate_min_length(const char *str) {
    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    int count[256] = {0};
    for (size_t i = 0; i < len; i++) {
        unsigned char c = str[i];
        count[c]++;
    }

    int min_count = len;
    for (int i = 0; i < 256; i++) {
        if (count[i] > 0 && count[i] < min_count) {
            min_count = count[i];
        }
    }

    return len - min_count;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    int result = calculate_min_length(argv[1]);
    printf("%d\n", result);

    return 0;
}