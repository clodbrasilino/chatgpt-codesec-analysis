#include <stdio.h>
#include <limits.h>

int max_occurring_char(const char *str, char *result)
{
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    size_t i;
    unsigned char best = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    if (str[0] == '\0') {
        return -1;
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        counts[c]++;
        if (counts[c] > max_count) {
            max_count = counts[c];
            best = c;
        }
    }

    *result = (char)best;
    return 0;
}

int main(void)
{
    char buffer[256];
    char max_char = '\0';
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = 0;
    while (buffer[len] != '\0') {
        len++;
    }
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    if (max_occurring_char(buffer, &max_char) != 0) {
        fprintf(stderr, "Invalid or empty input\n");
        return 1;
    }

    if (printf("Maximum occurring character: %c\n", max_char) < 0) {
        return 1;
    }

    return 0;
}