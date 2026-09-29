#include <stdio.h>
#include <string.h>
#include <limits.h>

char most_common_char(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    size_t len = strlen(str);
    if (len == 0) {
        return '\0';
    }

    int counts[UCHAR_MAX + 1] = {0};
    size_t i;

    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        counts[c]++;
    }

    int max_count = -1;
    int max_index = 0;

    for (i = 0; i <= UCHAR_MAX; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            max_index = (int)i;
        }
    }

    return (char)max_index;
}

int main(void) {
    const char *text = "hello world";
    char result = most_common_char(text);

    if (result != '\0') {
        printf("%c\n", result);
    }

    return 0;
}