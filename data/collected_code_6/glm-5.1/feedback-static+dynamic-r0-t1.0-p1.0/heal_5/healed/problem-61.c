#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int count_substrings(const char *s, size_t len) {
    if (s == NULL || len == 0) {
        return 0;
    }

    int count = 0;

    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)s[i])) {
            continue;
        }
        int sum = 0;
        for (size_t j = i; j < len; j++) {
            if (!isdigit((unsigned char)s[j])) {
                break;
            }
            sum += s[j] - '0';
            if (sum == (int)(j - i + 1)) {
                count++;
            } else if (sum > (int)(j - i + 1)) {
                break;
            }
        }
    }
    return count;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }
    
    int result = count_substrings(input, len);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}