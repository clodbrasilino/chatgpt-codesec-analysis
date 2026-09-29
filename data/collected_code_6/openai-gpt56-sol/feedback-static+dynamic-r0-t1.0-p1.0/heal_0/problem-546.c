#include <stdio.h>
#include <stddef.h>

const char *find_last_char(const char *string, int character)
{
    const char *last = NULL;
    unsigned char target = (unsigned char)character;

    if (string == NULL) {
        return NULL;
    }

    do {
        if ((unsigned char)*string == target) {
            last = string;
        }
    } while (*string++ != '\0');

    return last;
}

int main(void)
{
    char string[1024];
    int character;
    const char *result;

    if (fgets(string, sizeof string, stdin) == NULL) {
        return 1;
    }

    for (size_t i = 0; string[i] != '\0'; ++i) {
        if (string[i] == '\n') {
            string[i] = '\0';
            break;
        }
    }

    character = getchar();
    if (character == EOF) {
        return 1;
    }

    result = find_last_char(string, character);
    if (result == NULL) {
        puts("Character not found");
    } else {
        printf("%td\n", result - string);
    }

    return 0;
}