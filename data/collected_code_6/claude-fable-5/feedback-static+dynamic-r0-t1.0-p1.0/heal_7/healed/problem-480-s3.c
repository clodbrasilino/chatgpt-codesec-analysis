#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

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
    char buffer[BUFFER_SIZE];
    char max_char = '\0';
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strcspn(buffer, "\n");
    if (len < sizeof(buffer)) {
        buffer[len] = '\0';
    }

    if (max_occurring_char(buffer, &max_char) != 0) {
        fprintf(stderr, "Invalid or empty input\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum occurring character: %c\n", max_char) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}