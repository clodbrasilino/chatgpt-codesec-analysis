#include <stdio.h>
#include <string.h>

void remove_spaces(char *string)
{
    char *source = string;
    char *destination = string;

    while (*source != '\0') {
        if (*source != ' ') {
            *destination++ = *source;
        }
        source++;
    }

    *destination = '\0';
}

int main(void)
{
    char string[1024];

    if (fgets(string, sizeof string, stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return 1;
        }
        return 0;
    }

    string[strcspn(string, "\n")] = '\0';
    remove_spaces(string);

    if (printf("%s\n", string) < 0) {
        fprintf(stderr, "Failed to write output.\n");
        return 1;
    }

    return 0;
}