#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int is_word_character(unsigned char character)
{
    return isalnum(character) != 0 || character == '_';
}

static int abbreviate_road(char *text)
{
    char *read_position;
    char *write_position;
    unsigned char previous_character = 0;
    int has_previous_character = 0;

    if (text == NULL) {
        return -1;
    }

    read_position = text;
    write_position = text;

    while (*read_position != '\0') {
        int starts_word = !has_previous_character ||
                          !is_word_character(previous_character);

        if (starts_word &&
            read_position[0] == 'r' &&
            read_position[1] == 'o' &&
            read_position[2] == 'a' &&
            read_position[3] == 'd' &&
            !is_word_character((unsigned char)read_position[4])) {
            write_position[0] = 'r';
            write_position[1] = 'd';
            write_position[2] = '.';
            write_position += 3;
            read_position += 4;
            previous_character = (unsigned char)'d';
        } else {
            previous_character = (unsigned char)*read_position;
            *write_position++ = *read_position++;
        }

        has_previous_character = 1;
    }

    *write_position = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        if (fputs("Usage: program \"text\"\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (abbreviate_road(argv[1]) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(argv[1]) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}