#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char first_non_repeated_char(const char *str) {
    size_t len;
    unsigned int counts[UCHAR_MAX + 1] = {0};
    unsigned char c;

    if (str == NULL) {
        return '\0';
    }

    len = strlen(str);
    if (len == 0) {
        return '\0';
    }

    for (size_t i = 0; i < len; i++) {
        c = (unsigned char)str[i];
        counts[c]++;
    }

    for (size_t i = 0; i < len; i++) {
        c = (unsigned char)str[i];
        if (counts[c] == 1) {
            return (char)c;
        }
    }

    return '\0';
}

int main(int argc, char *argv[]) {
    char result;
    const char *test_str;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    test_str = argv[1];
    result = first_non_repeated_char(test_str);

    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No non-repeated character found.\n");
    }

    return EXIT_SUCCESS;
}