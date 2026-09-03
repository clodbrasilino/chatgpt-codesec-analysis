#include <stdio.h>
#include <string.h>
#include <limits.h>

int first_repeated_character(const char *str) {
    size_t char_count[UCHAR_MAX + 1] = {0};
    const unsigned char *ptr;
    size_t i = 0;

    if (str == NULL) {
        return -1;
    }

    ptr = (const unsigned char *)str;

    while (ptr[i] != '\0') {
        char_count[ptr[i]]++;
        i++;
    }

    i = 0;
    while (ptr[i] != '\0') {
        if (char_count[ptr[i]] > 1) {
            return ptr[i];
        }
        i++;
    }

    return -1;
}

int main(void) {
    char input[256];
    int result;
    char *newline;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    newline = strchr(input, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

    result = first_repeated_character(input);

    if (result != -1) {
        printf("%c\n", result);
    } else {
        printf("No repeated character\n");
    }

    return 0;
}