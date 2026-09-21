#include <stdio.h>
#include <limits.h>

char most_common_char(const char *str) {
    int counts[UCHAR_MAX + 1] = {0};
    size_t i = 0;

    while (str[i] != '\0') {
        counts[(unsigned char)str[i]]++;
        i++;
    }

    if (i == 0) {
        return '\0';
    }

    int max_count = 0;
    char max_char = '\0';

    for (size_t j = 0; j <= UCHAR_MAX; j++) {
        if (counts[j] > max_count) {
            max_count = counts[j];
            max_char = (char)j;
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