#include <stdio.h>

char find_max_occurring_char(const char *str) {
    if (str == NULL || *str == '\0') {
        return '\0';
    }

    int count[256] = {0};
    int max_count = 0;
    char max_char = '\0';
    size_t i = 0;

    while (str[i] != '\0') {
        unsigned char uc = (unsigned char)str[i];
        count[uc]++;
        if (count[uc] > max_count) {
            max_count = count[uc];
            max_char = str[i];
        }
        i++;
    }

    return max_char;
}

int main(void) {
    const char *text = "experience";
    char result = find_max_occurring_char(text);

    if (result != '\0') {
        printf("%c\n", result);
    }

    return 0;
}