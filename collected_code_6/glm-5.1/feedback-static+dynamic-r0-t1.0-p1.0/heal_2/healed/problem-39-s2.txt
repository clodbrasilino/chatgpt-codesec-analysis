#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int can_rearrange(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strnlen(str, 1024 * 1024);
    if (len <= 1) {
        return 1;
    }

    int count[256] = {0};
    int max_count = 0;

    for (size_t i = 0; i < len; i++) {
        unsigned char c = str[i];
        count[c]++;
        if (count[c] > max_count) {
            max_count = count[c];
        }
    }

    if (max_count > (int)((len + 1) / 2)) {
        return 0;
    }

    return 1;
}

int main(int argc, char const * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = can_rearrange(argv[1]);
    
    if (result) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return EXIT_SUCCESS;
}