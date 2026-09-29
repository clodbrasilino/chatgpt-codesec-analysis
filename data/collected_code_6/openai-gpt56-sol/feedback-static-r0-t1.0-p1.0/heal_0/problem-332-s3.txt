#include <limits.h>
#include <stddef.h>
#include <stdio.h>

static int count_character_frequency(const char *string,
                                     size_t frequencies[UCHAR_MAX + 1])
{
    const unsigned char *current;

    if (string == NULL || frequencies == NULL) {
        return -1;
    }

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        frequencies[i] = 0;
    }

    current = (const unsigned char *)string;

    while (*current != '\0') {
        if (frequencies[*current] == SIZE_MAX) {
            return -1;
        }

        ++frequencies[*current];
        ++current;
    }

    return 0;
}

int main(void)
{
    char input[1024];
    size_t frequencies[UCHAR_MAX + 1];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        input[0] = '\0';
    }

    if (count_character_frequency(input, frequencies) != 0) {
        return 1;
    }

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequencies[i] != 0) {
            if (printf("%u: %zu\n", (unsigned int)i, frequencies[i]) < 0) {
                return 1;
            }
        }
    }

    return 0;
}