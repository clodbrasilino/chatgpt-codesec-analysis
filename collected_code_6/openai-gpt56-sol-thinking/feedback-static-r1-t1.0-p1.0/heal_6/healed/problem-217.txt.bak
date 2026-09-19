#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

bool find_first_repeated_character(const char *string, unsigned char *result)
{
    bool seen[UCHAR_MAX + 1] = { false };

    if (string == NULL || result == NULL) {
        return false;
    }

    for (const unsigned char *current = (const unsigned char *)string;
         *current != '\0';
         ++current) {
        if (seen[*current]) {
            *result = *current;
            return true;
        }

        seen[*current] = true;
    }

    return false;
}

int main(int argc, char *argv[const])
{
    unsigned char repeated_character;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return 1;
    }

    const char *input = argv[1];

    if (find_first_repeated_character(input, &repeated_character)) {
        printf("%c\n", (int)repeated_character);
    } else {
        puts("No repeated character found");
    }

    return 0;
}