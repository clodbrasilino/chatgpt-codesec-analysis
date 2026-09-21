#include <stdio.h>
#include <string.h>

static size_t safe_strnlen(const char *s, size_t maxlen) {
    size_t len = 0;
    while (len < maxlen && s[len] != '\0') {
        ++len;
    }
    return len;
}

size_t minimizeLength(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return (size_t)-1;
    }

    size_t len = safe_strnlen(str, size);
    if (len == size) {
        return (size_t)-1;
    }

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    size_t result = minimizeLength(input, sizeof(input));
    if (result == (size_t)-1) {
        return 1;
    }

    printf("%zu\n", result);
    return 0;
}