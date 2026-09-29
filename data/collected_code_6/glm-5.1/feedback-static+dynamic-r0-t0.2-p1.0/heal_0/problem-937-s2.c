#include <stdio.h>
#include <string.h>
#include <limits.h>

char most_common_char(const char *str) {
    int counts[UCHAR_MAX + 1] = {0};
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        counts[(unsigned char)str[i]]++;
    }

    int max_count = 0;
    char max_char = '\0';

    for (size_t i = 0; i < len; i++) {
        unsigned char c = str[i];
        if (counts[c] > max_count) {
            max_count = counts[c];
            max_char = (char)c;
        }
    }

    return max_char;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    if (argv[1][0] == '\0') {
        fprintf(stderr, "Error: Input string cannot be empty.\n");
        return 1;
    }

    char result = most_common_char(argv[1]);
    printf("%c\n", result);

    return 0;
}