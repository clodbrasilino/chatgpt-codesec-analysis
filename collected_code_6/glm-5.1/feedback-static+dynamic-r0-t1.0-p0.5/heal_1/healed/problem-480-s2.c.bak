#include <stdio.h>
#include <string.h>

char find_max_occurring_char(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    size_t len = strlen(str);
    if (len == 0) {
        return '\0';
    }

    int count[256] = {0};
    size_t i;
    int max_count = 0;
    char max_char = '\0';

    for (i = 0; i < len; i++) {
        unsigned char uc = (unsigned char)str[i];
        count[uc]++;
        if (count[uc] > max_count) {
            max_count = count[uc];
            max_char = str[i];
        }
    }

    return max_char;
}

int main(void) {
    const char *text = "experience";
    char result = find_max_occurring_char(text);

    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("Empty string\n");
    }

    return 0;
}