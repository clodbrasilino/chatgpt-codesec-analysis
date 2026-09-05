#include <stdio.h>
#include <string.h>
#include <limits.h>

char most_common_char(const char *str) {
    size_t count[UCHAR_MAX + 1] = {0};
    size_t len = strlen(str);
    size_t max_count = 0;
    char result = '\0';

    if (str == NULL || len == 0) {
        return '\0';
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        count[c]++;
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (count[c] > max_count) {
            max_count = count[c];
            result = str[i];
        }
    }

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char res = most_common_char(argv[1]);
    if (res == '\0') {
        fprintf(stderr, "Input string is empty or invalid.\n");
        return 1;
    }

    printf("%c\n", res);
    return 0;
}