#include <stdio.h>

char get_most_common_char(const char *str) {
    if (str == NULL || *str == '\0') {
        return '\0';
    }

    unsigned int counts[256] = {0};
    unsigned int max_count = 0;
    char most_common = '\0';

    const unsigned char *p = (const unsigned char *)str;

    while (*p != '\0') {
        counts[*p]++;
        if (counts[*p] > max_count) {
            max_count = counts[*p];
            most_common = (char)*p;
        }
        p++;
    }

    return most_common;
}

int main(void) {
    const char *test_str = "experienced c developer";
    char result = get_most_common_char(test_str);

    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("Error: Invalid or empty string provided.\n");
    }

    return 0;
}