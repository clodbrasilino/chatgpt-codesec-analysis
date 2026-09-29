#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool matches_pattern(const char *string)
{
    if (string == NULL || string[0] != 'a') {
        return false;
    }

    const char *last = string;

    while (last[1] != '\0') {
        ++last;
    }

    return last != string && *last == 'b';
}

int main(int argc, const char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return 1;
    }

    puts(matches_pattern(argv[1]) ? "Match" : "No match");
    return 0;
}