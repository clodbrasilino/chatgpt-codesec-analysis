#include <stdio.h>
#include <string.h>
#include <limits.h>

char count_most_common_char(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return '\0';
    }

    size_t counts[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    char most_common = '\0';

    for (const char *p = str; *p != '\0'; p++) {
        unsigned char c = (unsigned char)*p;
        counts[c]++;
    }

    for (size_t i = 0; i <= UCHAR_MAX; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            most_common = (char)i;
        }
    }

    return most_common;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char result = count_most_common_char(argv[1]);
    if (result != '\0') {
        printf("%c\n", result);
    }

    return 0;
}