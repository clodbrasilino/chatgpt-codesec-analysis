#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_first_repeated(const char *str, size_t max_len) {
    if (str == NULL) {
        return '\0';
    }

    const char *end = memchr(str, '\0', max_len);
    size_t len = end ? (size_t)(end - str) : max_len;

    if (len == 0) {
        return '\0';
    }

    int *char_set = (int *)calloc(256, sizeof(int));
    if (char_set == NULL) {
        return '\0';
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (char_set[c] == 1) {
            free(char_set);
            return str[i];
        }
        char_set[c] = 1;
    }

    free(char_set);
    return '\0';
}

int main(void) {
    const char *test_str = "programming";
    char result = find_first_repeated(test_str, 256);

    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("No repeated character found\n");
    }

    return 0;
}