#include <stdio.h>
#include <string.h>

static void remove_character(char *string, char character)
{
    char *source;
    char *destination;

    if (string == NULL) {
        return;
    }

    source = string;
    destination = string;

    while (*source != '\0') {
        if (*source != character) {
            *destination++ = *source;
        }
        ++source;
    }

    *destination = '\0';
}

int main(void)
{
    char string[1024];
    char character_line[1024];
    size_t length;

    if (fgets(string, sizeof string, stdin) == NULL) {
        return 1;
    }

    length = strcspn(string, "\n");
    if (string[length] == '\n') {
        string[length] = '\0';
    } else if (!feof(stdin)) {
        int input;

        while ((input = fgetc(stdin)) != '\n' && input != EOF) {
        }

        if (ferror(stdin)) {
            return 1;
        }
    }

    if (fgets(character_line, sizeof character_line, stdin) == NULL) {
        return 1;
    }

    if (character_line[0] == '\n' || character_line[0] == '\0') {
        return 1;
    }

    length = strcspn(character_line, "\n");
    if (character_line[length] != '\n' && !feof(stdin)) {
        int input;

        while ((input = fgetc(stdin)) != '\n' && input != EOF) {
        }

        if (ferror(stdin)) {
            return 1;
        }
    }

    remove_character(string, character_line[0]);

    if (puts(string) == EOF) {
        return 1;
    }

    return 0;
}