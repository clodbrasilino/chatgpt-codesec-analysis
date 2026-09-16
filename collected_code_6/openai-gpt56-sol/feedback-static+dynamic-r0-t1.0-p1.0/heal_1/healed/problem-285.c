#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool matches_pattern(const char *string)
{
    size_t index = 0;
    size_t b_count = 0;

    if (string == NULL || string[index] != 'a') {
        return false;
    }

    ++index;

    while (string[index] == 'b' && b_count < 3U) {
        ++b_count;
        ++index;
    }

    return b_count >= 2U && string[index] == '\0';
}

int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 2;
    }

    if (matches_pattern(argv[1])) {
        puts("Match");
        return 0;
    }

    puts("No match");
    return 1;
}