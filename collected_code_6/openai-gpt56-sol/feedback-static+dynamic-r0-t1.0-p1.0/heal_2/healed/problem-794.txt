#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *string)
{
    if (string == NULL) {
        return false;
    }

    const size_t length = strlen(string);

    return length >= 2 && string[0] == 'a' && string[length - 1] == 'b';
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                (argc > 0 && argv != NULL && argv[0] != NULL)
                    ? argv[0]
                    : "program");
        return 1;
    }

    puts(matches_pattern(argv[1]) ? "Match" : "No match");

    return 0;
}