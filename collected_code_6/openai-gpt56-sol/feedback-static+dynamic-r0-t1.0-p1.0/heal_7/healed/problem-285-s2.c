#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *string)
{
    return string != NULL &&
           (strcmp(string, "abb") == 0 || strcmp(string, "abbb") == 0);
}

int main(void)
{
    char input[64];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        char discard[64];

        do {
            if (fgets(discard, sizeof discard, stdin) == NULL) {
                if (ferror(stdin)) {
                    return 1;
                }
                break;
            }
        } while (strchr(discard, '\n') == NULL);

        return puts("No match") == EOF ? 1 : 0;
    }

    return puts(matches_pattern(input) ? "Match" : "No match") == EOF ? 1 : 0;
}