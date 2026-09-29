#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2 &&
           string[0] == 'a' &&
           string[length - 1] == 'b';
}

int main(int argc, char *argv[])
{
    const char *const *const args = (const char *const *)argv;

    if (argc != 2 || args == NULL || args[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n",
                (argc > 0 && args != NULL && args[0] != NULL)
                    ? args[0]
                    : "program");
        return 1;
    }

    size_t length = 0;
    while (args[1][length] != '\0') {
        ++length;
    }

    puts(matches_pattern(args[1], length) ? "Match" : "No match");
    return 0;
}