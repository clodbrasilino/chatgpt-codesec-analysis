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

int main(int argc, char *const argv[])
{
    unsigned char repeated_character;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return 1;
    }

    if (find_first_repeated_character(argv[1], &repeated_character)) {
        printf("%c\n", (int)repeated_character);
    } else {
        puts("No repeated character found");
    }

    return 0;
}