#include <stdio.h>
#include <stdlib.h>

#define ASCII_CHARS 256

char get_max_occurring_char(const char *str);

char get_max_occurring_char(const char *str) {
    int count[ASCII_CHARS] = {0};
    int max_count = -1;
    char max_char = '\0';
    size_t i;

    if (str == NULL || str[0] == '\0') {
        return '\0';
    }

    for (i = 0; str[i] != '\0'; i++) {
        count[(unsigned char)str[i]]++;
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (max_count < count[(unsigned char)str[i]]) {
            max_count = count[(unsigned char)str[i]];
            max_char = str[i];
        }
    }

    return max_char;
}

int main(void) {
    const char *test_string = "success";
    char result = get_max_occurring_char(test_string);

    if (result != '\0') {
        printf("%c\n", result);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}