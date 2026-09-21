#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2 &&
           string[0] == 'a' &&
           string[length - 1] == 'b';
}

int main(int argc, char *const argv[])
{
    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n",
                (argc > 0 && argv != NULL && argv[0] != NULL)
                    ? argv[0]
                    : "program");
        return 1;
    }

    const size_t length = strlen(argv[1]);

    puts(matches_pattern(argv[1], length) ? "Match" : "No match");
    return 0;
}