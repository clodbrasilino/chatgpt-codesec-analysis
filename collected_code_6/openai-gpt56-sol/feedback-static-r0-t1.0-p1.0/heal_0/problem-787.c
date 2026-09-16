#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches(const char *str)
{
    return str != NULL && strcmp(str, "abbb") == 0;
}

int main(void)
{
    char input[128];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        return 0;
    }

    input[strcspn(input, "\r\n")] = '\0';
    printf("%s\n", matches(input) ? "Match" : "No match");

    return 0;
}