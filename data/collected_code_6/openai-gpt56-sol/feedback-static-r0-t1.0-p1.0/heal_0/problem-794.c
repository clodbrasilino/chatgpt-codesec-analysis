#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *string)
{
    size_t length;

    if (string == NULL) {
        return false;
    }

    length = strlen(string);

    return length >= 2U && string[0] == 'a' && string[length - 1U] == 'b';
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    if (matches_pattern(argv[1])) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}