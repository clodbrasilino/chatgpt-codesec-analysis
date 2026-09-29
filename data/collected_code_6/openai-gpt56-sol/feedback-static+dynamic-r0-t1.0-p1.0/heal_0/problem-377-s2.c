#include <stdio.h>
#include <string.h>

void remove_character(char *string, char character)
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
    int input;
    int character;

    if (fgets(string, sizeof string, stdin) == NULL) {
        return 1;
    }

    string[strcspn(string, "\n")] = '\0';

    character = getchar();
    if (character == EOF) {
        return 1;
    }

    while ((input = getchar()) != '\n' && input != EOF) {
    }

    remove_character(string, (char)character);
    puts(string);

    if (ferror(stdin) || ferror(stdout)) {
        return 1;
    }

    return 0;
}