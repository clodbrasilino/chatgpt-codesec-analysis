#include <limits.h>
#include <stddef.h>
#include <stdio.h>

static void count_character_frequency(const char *string, size_t frequency[UCHAR_MAX + 1])
{
    const unsigned char *current = (const unsigned char *)string;

    while (*current != '\0') {
        ++frequency[*current];
        ++current;
    }
}

int main(void)
{
    char input[1024];
    size_t frequency[UCHAR_MAX + 1] = {0};

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return 1;
        }
        return 0;
    }

    count_character_frequency(input, frequency);

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequency[i] != 0) {
            printf("0x%02zX: %zu\n", i, frequency[i]);
        }
    }

    return 0;
}