#include <stdio.h>
#include <string.h>

size_t minimizeLength(char *str) {
    if (str == NULL) {
        return (size_t)-1;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    unsigned long frequency[256] = {0};
    unsigned char maxChar = 0;
    size_t maxFrequency = 0;

    for (size_t i = 0; i < len; ++i) {
        unsigned char ch = (unsigned char)str[i];
        ++frequency[ch];
        if (frequency[ch] > maxFrequency) {
            maxFrequency = frequency[ch];
            maxChar = ch;
        }
    }

    size_t writeIndex = 0;
    for (size_t i = 0; i < len; ++i) {
        if ((unsigned char)str[i] != maxChar) {
            str[writeIndex++] = str[i];
        }
    }
    str[writeIndex] = '\0';

    return writeIndex;
}

int main(void) {
    char input[1024];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    size_t result = minimizeLength(input);
    if (result == (size_t)-1) {
        return 1;
    }

    printf("%zu\n", result);
    return 0;
}