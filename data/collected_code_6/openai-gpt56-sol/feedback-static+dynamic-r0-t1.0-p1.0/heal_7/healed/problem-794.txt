#include <stdbool.h>
#include <stdio.h>

static bool matches_pattern(const char *string)
{
    if (string == NULL || string[0] != 'a' || string[1] == '\0') {
        return false;
    }

    const char *current = string + 1;

    while (current[1] != '\0') {
        ++current;
    }

    return *current == 'b';
}

int main(int argc, const char *const argv[])
{
    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return 1;
    }

    puts(matches_pattern(argv[1]) ? "Match" : "No match");
    return 0;
}