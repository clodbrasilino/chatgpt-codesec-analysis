#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

bool find_first_repeated_character(const char *const string,
                                   unsigned char *const result)
{
    bool seen[UCHAR_MAX + 1U] = { false };

    if (string == NULL || result == NULL) {
        return false;
    }

    const unsigned char *current = (const unsigned char *)string;

    while (*current != '\0') {
        if (seen[*current]) {
            *result = *current;
            return true;
        }

        seen[*current] = true;
        ++current;
    }

    return false;
}

int main(int argc, char **const argv)
{
    unsigned char repeated_character;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program_name =
            argv != NULL && argc > 0 && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return 1;
    }

    if (find_first_repeated_character(argv[1], &repeated_character)) {
        printf("%c\n", (int)repeated_character);
    } else {
        puts("No repeated character found");
    }

    return 0;
}