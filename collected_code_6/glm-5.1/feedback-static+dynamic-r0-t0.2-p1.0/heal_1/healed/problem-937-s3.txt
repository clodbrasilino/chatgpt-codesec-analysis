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

    size_t count[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    char result = '\0';

    for (size_t i = 0; i < len; i++) {
        unsigned char uc = (unsigned char)str[i];
        count[uc]++;
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char uc = (unsigned char)str[i];
        if (count[uc] > max_count) {
            max_count = count[uc];
            result = str[i];
        }
    }

    return result;
}

int main(void) {
    const char *text = "improper handling of exceptional conditions";
    char res = most_common_char(text);

    if (res != '\0') {
        printf("%c\n", res);
    }

    return 0;
}