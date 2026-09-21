#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2U &&
           string[0] == 'a' &&
           string[length - 1U] == 'b';
}

int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    if (matches_pattern(argv[1], strlen(argv[1]))) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}