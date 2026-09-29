#include <stdbool.h>
#include <stdio.h>

bool find_first_repeated_character(const char *string, unsigned char *result)
{
    if (string == NULL || result == NULL) {
        return false;
    }

    for (const char *current = string; *current != '\0'; ++current) {
        for (const char *previous = string; previous < current; ++previous) {
            if (*previous == *current) {
                *result = (unsigned char)*current;
                return true;
            }
        }
    }

    return false;
}

int main(int argc, const char *const argv[])
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