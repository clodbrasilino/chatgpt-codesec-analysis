#include <stdio.h>
#include <limits.h>
#include <stddef.h>

int find_max_occurring_char(const char *str, char *result)
{
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    size_t i;
    unsigned char max_char = 0;
    int found = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        counts[c]++;
        if (counts[c] > max_count) {
            max_count = counts[c];
            max_char = c;
            found = 1;
        }
    }

    if (found == 0) {
        return -1;
    }

    *result = (char)max_char;
    return 0;
}

int main(void)
{
    char input[256];
    char max_char;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    for (size_t i = 0; input[i] != '\0'; i++) {
        if (input[i] == '\n') {
            input[i] = '\0';
            break;
        }
    }

    if (find_max_occurring_char(input, &max_char) != 0) {
        fprintf(stderr, "Empty string or invalid input\n");
        return 1;
    }

    if (printf("Maximum occurring character: %c\n", max_char) < 0) {
        return 1;
    }

    return 0;
}