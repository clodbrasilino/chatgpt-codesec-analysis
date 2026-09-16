#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool can_rearrange_without_adjacent_duplicates(const char *string)
{
    size_t frequencies[256] = {0};
    size_t length;
    size_t maximum = 0;

    if (string == NULL) {
        return false;
    }

    length = strlen(string);

    for (size_t i = 0; i < length; ++i) {
        const unsigned char character = (unsigned char)string[i];

        ++frequencies[character];
        if (frequencies[character] > maximum) {
            maximum = frequencies[character];
        }
    }

    return maximum <= (length + 1U) / 2U;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    size_t length = strlen(input);

    if (length > 0U && input[length - 1U] == '\n') {
        input[--length] = '\0';

        if (length > 0U && input[length - 1U] == '\r') {
            input[length - 1U] = '\0';
        }
    } else if (!feof(stdin)) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        return 1;
    }

    puts(can_rearrange_without_adjacent_duplicates(input) ? "true" : "false");

    return 0;
}