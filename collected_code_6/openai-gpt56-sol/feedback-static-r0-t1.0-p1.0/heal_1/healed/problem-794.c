#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *string)
{
    if (string == NULL) {
        return false;
    }

    const size_t length = strlen(string);

    return length >= 2U && string[0] == 'a' && string[length - 1U] == 'b';
}

int main(int argc, char * const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    puts(matches_pattern(argv[1]) ? "Match" : "No match");

    return 0;
}